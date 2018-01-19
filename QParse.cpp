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

QParse *QParse::sInstance = nullptr;

void QParse::initialize(const QByteArray &url, const QByteArray &appId, const QByteArray &apiKey, QObject *parent)
{
    if(sInstance) return;
    sInstance = new QParse(url, appId, apiKey, parent);
}

QParse* QParse::getInstance(QObject *parent)
{
    if(!sInstance) {
        sInstance = new QParse(parent);
    }
    return sInstance;
}

QParse* QParse::getInstance(const QByteArray &url, const QByteArray &appId, const QByteArray &apiKey, QObject *parent)
{
    if(!sInstance) {
        sInstance = new QParse(url, appId, apiKey, parent);
    }
    return sInstance;
}

QParse::QParse(QObject *parent) : QObject(parent)
{

}

QParse::QParse(const QByteArray &url, const QByteArray &appId, const QByteArray &apiKey, QObject *parent) :
    QObject(parent), mUrl(url), mAppId(appId), mApiKey(apiKey)
{

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

