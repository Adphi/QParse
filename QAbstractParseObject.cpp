/*****************************************************************************
 *
 * QParseObject.cpp
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
#include "QAbstractParseObject.h"
#include "QParseObjectManager.h"
#include <QDebug>

QAbstractParseObject::QAbstractParseObject(QObject *parent) : QObject(parent)
{
    qDebug() << "Creating QAbstractParseObject";
}

void QAbstractParseObject::save()
{
    auto manager = QParseObjectManager::getInstance();
    manager->save(this);
    connect(manager, SIGNAL(saved(QAbstractParseObject*)),
            this, SIGNAL(saved()),
            Qt::UniqueConnection);
}

void QAbstractParseObject::update()
{
    auto manager = QParseObjectManager::getInstance();
    manager->update(this);
    connect(manager, SIGNAL(updated(QAbstractParseObject*)),
            this, SIGNAL(updated()),
            Qt::UniqueConnection);

}

void QAbstractParseObject::remove()
{
    auto manager = QParseObjectManager::getInstance();
    manager->remove(this);
    connect(manager, SIGNAL(removed()),
            this, SIGNAL(removed()),
            Qt::UniqueConnection);
}

QJsonObject QAbstractParseObject::serialize() const
{
    QJsonObject json = serialize_impl();
    //json["objectId"] = mObjectId;
    if(!mUpdatedAt.isNull())
        json["updatedAt"] = QJsonObject {
            {"__type", "Date"},
            {"iso", mUpdatedAt.toString(Qt::ISODate)}
    };
    if(!mCreatedAt.isNull())
        json["createdAt"] = QJsonObject {
        {"__type", "Date"},
        {"iso", mCreatedAt.toString(Qt::ISODate)}
    };
    return json;
}

void QAbstractParseObject::deserialize(const QJsonObject &json)
{
    deserialize_impl(json);
    if(json.contains("objectId"))
        mObjectId = json["objectId"].toString();
    if(json.contains("createdAt"))
        mCreatedAt = QDateTime::fromString(json["createdAt"].toString(), Qt::ISODate);
    if(json.contains("updatedAt"))
        mUpdatedAt = QDateTime::fromString(json["updatedAt"].toString(), Qt::ISODate);
}

QString QAbstractParseObject::objectId() const
{
    return mObjectId;
}

void QAbstractParseObject::setObjectId(const QString &objectId)
{
    if(objectId != mObjectId) {
        mObjectId = objectId;
        emit objectIdChanged();
    }
}

QDateTime QAbstractParseObject::updatedAt() const
{
    return mUpdatedAt;
}

void QAbstractParseObject::setUpdatedAt(const QDateTime &updatedAt)
{
    if(mUpdatedAt != updatedAt) {
        mUpdatedAt = updatedAt;
        emit updatedAtChanged();
    }
}

QDateTime QAbstractParseObject::createdAt() const
{
    return mCreatedAt;
}

void QAbstractParseObject::setCreatedAt(const QDateTime &createdAt)
{
    if(mCreatedAt != createdAt) {
        mCreatedAt = createdAt;
        emit createdAtChanged();
    }
}

//QParseObject* QParseObject::fromJson(const QJsonObject &jsonObject, QObject *parent)
//{
//    QParseObject *object = new QParseObject(parent);
//    object->mCreatedAt = QDateTime::fromString(jsonObject["createdAt"].toString(), Qt::ISODateWithMs);
//    object->mUpdatedAt = QDateTime::fromString(jsonObject["updatedAt"].toString(), Qt::ISODateWithMs);
//    object->mObjectId = jsonObject["objectId"].toString();
//    return object;
//}
QDebug operator<<(QDebug debug, const QAbstractParseObject &o)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << '('
          << o.objectId() << ", "
          << o.createdAt() << ", "
          << o.updatedAt() << ")";

    return debug;
}
