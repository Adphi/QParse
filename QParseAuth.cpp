/*****************************************************************************
 *
 * QParseUser.cpp
 *
 * Created: 19 2018 by Philippe-Adrien
 *
 * Copyright 2018 Philippe-Adrien. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *****************************************************************************/
#include "QParseAuth.h"

#include <QUrlQuery>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtPropertySerializer.h>

QByteArray QParseAuth::SIGN_UP = "/users";
QByteArray QParseAuth::LOGIN = "/login";
QByteArray QParseAuth::LOGOUT = "/logout";
QByteArray QParseAuth::VERIFICATION_EMAIL_REQUEST = "/verificationEmailRequest";
QByteArray QParseAuth::REQUEST_PASSWORD_RESET = "/requestPasswordReset";
QByteArray QParseAuth::USERS = "/users";

QParseAuth *QParseAuth::sInstance = nullptr;


QParseAuth::QParseAuth(QObject *parent) : QObject(parent)
{
    mParse = QParse::getInstance();
    mToken = mParse->settings()->value(QParse::SESSION_TOKEN, "").toString();
    mSignedIn = ! mToken.isEmpty();
    mManager = new QNetworkAccessManager(this);
}

QParseUser *QParseAuth::user() const
{
    return mUser;
}


/**
 * @brief QParseAuth::getInstance
 * @param parent
 * @return
 */
QParseAuth *QParseAuth::getInstance(QObject *parent)
{
    if( !sInstance ) {
        sInstance = new QParseAuth(parent);
    }
    return sInstance;
}

/**
 * @brief QParseAuth::signIn
 * @param name
 * @param password
 */
void QParseAuth::signIn(const QString &name, const QString &password) {
    if( !mToken.isEmpty() ) {
        qDebug() << "Already Signed In with token:" << mToken;
        emit signedInChanged(true);
        return;
    }
    //else if(mIsAuthenticating) return;

    mIsAuthenticating = true;
    QUrl url(mParse->url() + LOGIN);
    QUrlQuery query;
    query.addQueryItem("username", name);
    query.addQueryItem("password", password);
    url.setQuery(query.query());
    QNetworkRequest request(url);
    request.setRawHeader(QParse::APP_ID, mParse->appId());
    request.setRawHeader(QParse::REST_API_KEY, mParse->apiKey());
    request.setRawHeader(QParse::REVOCABLE_SESSION, mParse->revocableSession() ? "1" : "0");
    mReply = mManager->get(request);
    connect(mReply, &QNetworkReply::finished, [&](){
        if(mReply->error()) {
            qDebug() << mReply->readAll();
            mIsAuthenticating = false;
            return;
        }
        QJsonDocument doc = QJsonDocument::fromJson(QString(mReply->readAll()).toUtf8());
        const QJsonObject json = doc.object();
        mToken = json["sessionToken"].toString();
        mParse->settings()->setValue(QParse::SESSION_TOKEN, mToken);
        mSignedIn = true;
        qDebug() << "Session Token" << mParse->settings()->value(QParse::SESSION_TOKEN, "").toString();
        mUser = new QParseUser(this);
        QtPropertySerializer::deserialize(mUser, json.toVariantMap());
        qDebug() << mUser->username() << mUser->email() << mUser->objectId() << mUser->updatedAt();
        mReply->deleteLater();
        mIsAuthenticating = false;
        emit signedInChanged(true);
    });
}

/**
 * @brief QParseAuth::signOut
 */
void QParseAuth::signOut() {
    if(mToken.isEmpty()) {
        qDebug() << "Already Signed Out";
        emit signedInChanged(false);
        return;
    }
    else if(mIsAuthenticating) return;
    mIsAuthenticating = true;
    qDebug() << "Signing Out";
    QUrl url(mParse->url() + LOGOUT);
    QNetworkRequest request(url);
    request.setRawHeader(QParse::APP_ID, mParse->appId());
    request.setRawHeader(QParse::REST_API_KEY, mParse->apiKey());
    request.setRawHeader(QParse::SESSION_TOKEN, mToken.toUtf8());
    mReply = mManager->post(request, "");
    connect(mReply, &QNetworkReply::finished, [&](){
        if(mReply->error()) {
            qDebug() << "Could not signOut";
            mIsAuthenticating = false;
        }
        qDebug() << mReply->readAll();
        mParse->settings()->setValue (QParse::SESSION_TOKEN, "");
        mToken = "";
        mUser = nullptr;
        mSignedIn = false;
        mReply->deleteLater();
        mIsAuthenticating = false;
        emit signedInChanged(false);
    });
}

/**
 * @brief QParseAuth::signUp
 * @param name
 * @param email
 * @param password
 * @param phoneNumber
 */
void QParseAuth::signUp(const QString &name, const QString &email, const QString &password, const QString &phone)
{
    if(mSignedIn) {
        qDebug() << "Can't sign up, sign out first";
        return;
    }
    else if(mIsAuthenticating) return;

    mIsAuthenticating = true;
    qDebug() << "Signing Up" << name;
    mUser = new QParseUser(name, email, phone, this);
    auto request = mParse->request(SIGN_UP);
    request.setRawHeader("Content-Type", "application/json");
    QJsonObject data;
    data["username"] = name;
    data["email"] = email;
    data["password"] = password;
    data["phone"] = phone;
    mReply = mManager->post(request, QJsonDocument(data).toJson());
    connect(mReply, &QNetworkReply::finished, [&](){
        if(mReply->error()) {
            qDebug() << mReply->readAll();
            mIsAuthenticating = false;
            return;
        }
        QJsonDocument doc = QJsonDocument::fromJson(QString(mReply->readAll()).toUtf8());
        qDebug() << doc;
        const QJsonObject json = doc.object();
        mToken = json["sessionToken"].toString();
        mParse->settings()->setValue(QParse::SESSION_TOKEN, mToken);
        QtPropertySerializer::deserialize(mUser, json.toVariantMap());
        qDebug() << mUser->username() << mUser->email() << mUser->objectId() << mUser->updatedAt();
        mSignedIn = true;
        mIsAuthenticating = false;
        emit signedInChanged(true);
        mReply->deleteLater();
    });

}

/**
 * @brief QParseAuth::signedIn
 * @return
 */
bool QParseAuth::signedIn() const
{
    return mSignedIn;
}
