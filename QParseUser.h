/*****************************************************************************
 *
 * QParseUser.h
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
#ifndef QPARSEUSER_H
#define QPARSEUSER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

#include "QParse.h"


class QParseUser : public QObject
{
    Q_OBJECT
public:
    explicit QParseUser(QObject *parent = nullptr);
    Q_INVOKABLE void signIn(const QString& name, const QString& password) const;
    Q_INVOKABLE void signOut() const;

    static QByteArray SIGN_UP;
    static QByteArray LOGIN;
    static QByteArray VERIFICATION_EMAIL_REQUEST;
    static QByteArray REQUEST_PASSWORD_RESET;
    static QByteArray USERS;

signals:

public slots:


private:
    QParse *mParse;
    QNetworkAccessManager *mManager;
};

#endif // QPARSEUSER_H
