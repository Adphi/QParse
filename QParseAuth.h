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

#include <QAbstractParseObject.h>
#include <QParse.h>
#include <QParseUser.h>

/**
 * @brief The QParseAuth class
 */
class QParseAuth : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE static QParseAuth* getInstance(QObject *parent = nullptr);
    Q_INVOKABLE void signIn(const QString& name, const QString& password);
    Q_INVOKABLE void signOut();
    Q_INVOKABLE void signUp(const QString& name, const QString& email, const QString& password, const QString& phoneNumber);
    Q_INVOKABLE void requestVerificationEmail();
    Q_INVOKABLE void requestPasswordReset(const QString& email);

    Q_PROPERTY(bool isSignedIn READ isSignedIn NOTIFY signedInChanged)
    Q_PROPERTY(QParseUser* user READ user NOTIFY userChanged)

    bool isSignedIn() const;

    QParseUser *user() const;


    QString token() const;

signals:
    void signedInChanged(bool isSignedIn);
    void userChanged(QParseUser* user);

public slots:

private:
    explicit QParseAuth(QObject *parent = nullptr);
    static QParseAuth *sInstance;
    // Auth State
    bool mIsSignedIn = false;
    QString mToken;
    QParseUser *mUser;
    bool mIsAuthenticating = false;

    QParse *mParse;
    QNetworkAccessManager *mManager;

    void retrieveSession();

    // Path
    static QByteArray SIGN_UP;
    static QByteArray SIGN_IN;
    static QByteArray SIGN_OUT;
    static QByteArray VERIFICATION_EMAIL_REQUEST;
    static QByteArray REQUEST_PASSWORD_RESET;
    static QByteArray USERS;
    static QByteArray VALIDATE_SESSION;
};

#endif // QPARSEUSER_H
