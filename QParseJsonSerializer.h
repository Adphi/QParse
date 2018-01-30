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



#include <QDebug>
namespace QParseJsonSerializer {


QVariantMap serialize(QObject *data)
{
    QVariantMap map;
    auto metaObject = data->metaObject();
    auto propertyCount = metaObject->propertyCount();

    for(auto i = 0; i < propertyCount; ++i)
    {
        auto propertyName = QByteArray(metaObject->property(i).name());
        auto value = data->property(propertyName);
        if(propertyName == "objectName")
            continue;
        if(value.canConvert<QVariantList>()) {
            QVariantList list;
            if(value.toList().isEmpty()) {
                QSequentialIterable iterable = value.value<QSequentialIterable>();
                for (const auto& v : iterable) {
                    if(auto o = qvariant_cast<QObject*>(v)) {
                        list << serialize(o);
                    }
                }
            }
            else {
                list = QVariantList(value.toList());
            }
            map[propertyName] = list;
            qDebug() << list;
        }
        else if(auto o = qvariant_cast<QObject*>(value)){
            qDebug() << "___Other Object___";
            map[propertyName] = serialize(o);
            qDebug() << "__________________";
        }
        else {
            qDebug() << propertyName << value;
            map[propertyName] = value;
        }
    }
    return map;
}

template <typename T>
T serialize(QVariant variant, T destination = nullptr) {
    T object;

}

}

#endif // QPARSEJSONSERIALIZER_H
