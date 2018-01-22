/*****************************************************************************
 *
 * QParse.cpp
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
#include "QParse.h"

QByteArray QParse::APP_ID = "X-Parse-Application-Id";
QByteArray QParse::REST_API_KEY = "X-Parse-REST-API-Key";
QByteArray QParse::REVOCABLE_SESSION = "X-Parse-Revocable-Session";
QByteArray QParse::SESSION_TOKEN = "X-Parse-Session-Token";
QByteArray QParse::MASTER_KEY = "X-Parse-Master-Key";

QParse *QParse::sInstance = nullptr;

/**
 * @brief QParse::initialize
 * @param url
 * @param appId
 * @param apiKey
 * @param parent
 */
void QParse::initialize(const QByteArray &url, const QByteArray &appId, const QByteArray &apiKey, QObject *parent)
{
    if(sInstance) return;
    qDebug() << "Creating QParseClient Instance";
    sInstance = new QParse(url, appId, apiKey, parent);
}

/**
 * @brief QParse::getInstance
 * @return
 */
QParse* QParse::getInstance()
{
    if(!sInstance) {
        QParseInitializeException exception;
        exception.raise();
    }
    return sInstance;
}

QParse::QParse(QObject *parent) : QObject(parent)
{

}

QParse::QParse(const QByteArray &url, const QByteArray &appId, const QByteArray &apiKey, QObject *parent) :
    QObject(parent), mUrl(url), mAppId(appId), mApiKey(apiKey)
{
    mSettings = new QSettings(this);
}

QByteArray QParse::masterKey() const
{
    return mMasterKey;
}

void QParse::setMasterKey(const QByteArray &masterKey)
{
    mMasterKey = masterKey;
}

/**
 * @brief QParse::settings
 * @return
 */
QSettings* QParse::settings() const
{
    return mSettings;
}

/**
 * @brief QParse::request
 * @param path
 * @return
 */
QNetworkRequest QParse::request(const QByteArray &path) const
{
    QUrl url(mUrl + path);
    QNetworkRequest request(url);
    request.setRawHeader(QParse::APP_ID, mAppId);
    request.setRawHeader(QParse::REST_API_KEY, mApiKey);
    return request;
}

bool QParse::revocableSession() const
{
    return mRevocableSession;
}

QByteArray QParse::apiKey() const
{
    return mApiKey;
}

QByteArray QParse::appId() const
{
    return mAppId;
}

QByteArray QParse::url() const
{
    return mUrl;
}

