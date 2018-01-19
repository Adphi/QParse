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
#include "QParseUser.h"

#include <QUrlQuery>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include "QParse.h"

QByteArray QParseUser::SIGN_UP = "/users";
QByteArray QParseUser::LOGIN = "/login";
QByteArray QParseUser::VERIFICATION_EMAIL_REQUEST = "/verificationEmailRequest";
QByteArray QParseUser::REQUEST_PASSWORD_RESET = "/requestPasswordReset";
QByteArray QParseUser::USERS = "/users";


QParseUser::QParseUser(QObject *parent) : QObject(parent)
{
    mParse = QParse::getInstance();
    mManager = new QNetworkAccessManager(this);
}

void QParseUser::signIn(const QString &name, const QString &password) const {
    QUrl url(mParse->url() + LOGIN);
    QUrlQuery query;
    query.addQueryItem("username", name);
    query.addQueryItem("password", password);
    url.setQuery(query.query());
    QNetworkRequest request(url);
    request.setRawHeader(QParse::APP_ID, mParse->appId());
    request.setRawHeader(QParse::REST_API_KEY, mParse->apiKey());
    request.setRawHeader(QParse::REVOCABLE_SESSION, mParse->revocableSession() ? "1" : "0");
    mManager->get(request);
    connect(mManager, &QNetworkAccessManager::finished, [&](QNetworkReply *reply){
        QJsonDocument doc = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
        qDebug() << doc;
        reply->deleteLater();
    });
}

void QParseUser::signOut() const {

}
