/*****************************************************************************
 *
 * Serializer.h
 *
 * Created: 27 2018 by Philippe-Adrien
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
#ifndef QPARSEJSONSERIALIZER_H
#define QPARSEJSONSERIALIZER_H

#include <QObject>

#include <QMetaObject>
#include <QMetaType>
#include <QMetaProperty>

#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <QSequentialIterable>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QRegularExpression>
#include <QDebug>

namespace QParseJsonSerializer {

QJsonObject jsonSerialize(QObject *data);


QObject* jsonDeserialize(const QJsonObject& json, QObject *object);

QObject* jsonDeserialize(const QJsonObject& json, const QString& className);

QVariantMap serialize(QObject *data);

QString getTypeName(QString propertyName, QObject* object);

template <typename T, typename std::enable_if<std::is_base_of<QObject, T>::value>::type* = nullptr>
T* deserialize(const QVariantMap& data, T *object);

}

#endif // QPARSEJSONSERIALIZER_H
