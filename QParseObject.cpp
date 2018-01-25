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
#include "QParseObject.h"
#include "QParseObjectManager.h"
#include <QDebug>

QParseObject::QParseObject(QObject *parent) : QObject(parent)
{
    qDebug() << "Creating QParseObject";
}

void QParseObject::save()
{
    auto manager = QParseObjectManager::getInstance();
    manager->save(this);
    connect(manager, &QParseObjectManager::saved, [&](){
        this->disconnect();
        emit saved();
    });
}

void QParseObject::update()
{
    auto manager = QParseObjectManager::getInstance();
    manager->update(this);
    connect(manager, &QParseObjectManager::updated, [&](){
        emit updated();
    });

}

void QParseObject::remove()
{
    auto manager = QParseObjectManager::getInstance();
    manager->remove(this);
    connect(manager, &QParseObjectManager::removed, [&](){
        emit removed();
    });
}

QString QParseObject::objectId() const
{
    return mObjectId;
}

void QParseObject::setObjectId(const QString &objectId)
{
    mObjectId = objectId;
}

QDateTime QParseObject::updatedAt() const
{
    return mUpdatedAt;
}

void QParseObject::setUpdatedAt(const QDateTime &updatedAt)
{
    mUpdatedAt = updatedAt;
}

QDateTime QParseObject::createdAt() const
{
    return mCreatedAt;
}

void QParseObject::setCreatedAt(const QDateTime &createdAt)
{
    mCreatedAt = createdAt;
}

//QParseObject* QParseObject::fromJson(const QJsonObject &jsonObject, QObject *parent)
//{
//    QParseObject *object = new QParseObject(parent);
//    object->mCreatedAt = QDateTime::fromString(jsonObject["createdAt"].toString(), Qt::ISODateWithMs);
//    object->mUpdatedAt = QDateTime::fromString(jsonObject["updatedAt"].toString(), Qt::ISODateWithMs);
//    object->mObjectId = jsonObject["objectId"].toString();
//    return object;
//}
