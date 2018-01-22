/*****************************************************************************
 *
 * QParse.h
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
#ifndef QPARSE_H
#define QPARSE_H

#include "qparse_global.h"

#include <QObject>
#include <QSettings>
#include <QException>
#include <QNetworkRequest>
#include <QDebug>

/**
 * @brief The QParse class
 */
class QParse : public QObject
{
    Q_OBJECT
public:
    static QByteArray APP_ID;
    static QByteArray REST_API_KEY;
    static QByteArray REVOCABLE_SESSION;
    static QByteArray SESSION_TOKEN;
    static QByteArray MASTER_KEY;

    static void initialize(const QByteArray& url, const QByteArray& appId, const QByteArray& apiKey, QObject *parent = nullptr);
    static QParse* getInstance();
    QParse* url(const QByteArray& url);
    QParse* appId(const QByteArray& appId);
    QParse* apiKey(const QByteArray& apiKey);

    QByteArray url() const;
    QByteArray appId() const;
    QByteArray apiKey() const;
    bool revocableSession() const;

    QSettings* settings() const;
    QNetworkRequest request(const QByteArray& path) const;

    QByteArray masterKey() const;
    void setMasterKey(const QByteArray &masterKey);

signals:

public slots:

private:
    explicit QParse(QObject *parent = nullptr);
    QParse(const QByteArray& url, const QByteArray& appId, const QByteArray& apiKey, QObject *parent = nullptr);
    Q_DISABLE_COPY(QParse)
    static QParse* sInstance;

    QSettings* mSettings;

    QByteArray mUrl;
    QByteArray mAppId;
    QByteArray mApiKey;
    QByteArray mMasterKey;
    bool mRevocableSession;
};

class QParseInitializeException : public QException
{
public:
    void raise() const {
        qDebug() << "QParse not Initialized";
        throw *this;
    }
    QParseInitializeException *clone() const { return new QParseInitializeException(*this); }
};

#endif // QPARSE_H

