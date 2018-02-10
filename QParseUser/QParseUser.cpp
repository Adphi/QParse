/*****************************************************************************
 *
 * QParseTest.cpp
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
#include "QParseUser.h"

QParseUser::QParseUser(QObject *parent) : QParseObject(parent)
{

}

QParseUser::QParseUser(const QString &username, const QString &email, const QString &phone, QObject *parent)
    : QParseObject(parent), mUsername(username), mEmail(email), mPhone(phone)
{

}

//QJsonObject QParseUser::serialize_impl() const
//{
//    QJsonObject json;
//    json["username"] = mUsername;
//    json["email"] = mEmail;
//    json["phone"] = mPhone;
//    return json;
//}

//void QParseUser::deserialize_impl(const QJsonObject &json)
//{
//    if(json.contains("username"))
//        mUsername = json["username"].toString();
//    if(json.contains("email"))
//        mEmail = json["email"].toString();
//    if(json.contains("phone"))
//        mPhone = json["phone"].toString();
//}

QString QParseUser::username() const
{
    return mUsername;
}

void QParseUser::setUsername(const QString &name)
{
    mUsername = name;
}

QString QParseUser::email() const
{
    return mEmail;
}

void QParseUser::setEmail(const QString &email)
{
    mEmail = email;
}

QString QParseUser::phone() const
{
    return mPhone;
}

void QParseUser::setPhone(const QString &phone)
{
    mPhone = phone;
}

QDebug operator<<(QDebug debug, const QParseUser &u)
{
    QDebugStateSaver saver(debug);
    debug << '(' << u.username() << ", " << u.email() << u.objectId() << ')';

    return debug;
}
