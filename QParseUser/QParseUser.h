/*****************************************************************************
 *
 * QParseTest.h
 *
 * Created: 20 2018 by Philippe-Adrien
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
#ifndef QPARSETEST_H
#define QPARSETEST_H

#include <QParseObject.h>
#include <QDebug>

/**
 * @brief The QParseUser class
 */
class QParseUser : public QParseObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)

public:
    explicit QParseUser(QObject *parent = nullptr);
    QParseUser(const QString &username, const QString &email, const QString &phone, QObject *parent = nullptr);

    QString username() const;
    void setUsername(const QString &username);

    QString email() const;
    void setEmail(const QString &email);

    QString phone() const;
    void setPhone(const QString &phone);

signals:
    void usernameChanged(QString username);
    void emailChanged(QString email);
    void phoneChanged(QString phone);

public slots:

private:
    QString mUsername;
    QString mEmail;
    QString mPhone;

//    virtual QJsonObject serialize_impl() const override;
//    virtual void deserialize_impl(const QJsonObject &json) override;
};
QDebug operator<<(QDebug debug, const QParseUser &u);
#endif // QPARSETEST_H
