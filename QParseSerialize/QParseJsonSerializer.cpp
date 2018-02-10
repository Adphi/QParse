/*****************************************************************************
 *
 * QParseJsonSerializer.cpp
 *
 * Created: 04 2018 by Philippe-Adrien
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

#include <QParseJsonSerializer.h>

QJsonObject QParseJsonSerializer::jsonSerialize(QObject *data)
{
    QJsonObject jsonObject;
    auto metaObject = data->metaObject();
    auto propertyCount = metaObject->propertyCount();

    for(auto i = 1; i < propertyCount; ++i)
    {
        auto propertyName = QByteArray(metaObject->property(i).name());
        auto value = data->property(propertyName);

        if(value.canConvert<QVariantList>()) {
            QJsonArray jsonArray;
            if(value.toList().isEmpty()) {
                auto it = value.value<QSequentialIterable>();
                for (const auto& v : it) {
                    if(auto o = qvariant_cast<QObject*>(v)) {
                        jsonArray << jsonSerialize(o);
                    }
                }
            }
            else {
                jsonArray = QJsonArray::fromVariantList(value.toList());
            }
            jsonObject[propertyName] = jsonArray;
        }
        else if(auto o = qvariant_cast<QObject*>(value)) {
            jsonObject[propertyName] = jsonSerialize(o);
        }
        else {
            jsonObject[propertyName] = QJsonValue::fromVariant(value);
        }
    }
    return jsonObject;
}


QObject* QParseJsonSerializer::jsonDeserialize(const QJsonObject& json, QObject *object)
{
    if(!object) {
        return object;
    }

    for(const auto& k : json.keys()) {
        auto v = json[k];
        qDebug() << k << v;
        if(v.isArray()) {
            auto array = v.toArray();
            QVariantList list;
            for(const auto& e : array) {
                if(e.isObject()) {
                    auto className = getTypeName(k.toUtf8(), object);
                    QRegularExpression regex("<(.*)>");
                    auto match = regex.match(className);
                    auto classObjectName = match.captured(1);
                    list << QVariant::fromValue(jsonDeserialize(e.toObject(), classObjectName));
                }
                else {
                    // TODO: not working...
                    list << QVariant::fromValue(e.toVariant());
                    qDebug() << list;
                }
            }
            object->setProperty(k.toUtf8(), list);
        }
        else if(v.isObject()) {
            auto o = v.toObject();
            auto typeName = getTypeName(k, object);
            object->setProperty(k.toUtf8(), QVariant::fromValue(jsonDeserialize(o, QString(typeName))));
        }
        else {
            object->setProperty(k.toUtf8(), QVariant::fromValue(v));
        }
    }
    return object;
}

QObject* QParseJsonSerializer::jsonDeserialize(const QJsonObject& json, const QString& className)
{
    auto type = QMetaType::type(className.toUtf8());
    auto metaObject = QMetaType::metaObjectForType(type);
    auto object = metaObject->newInstance();
    return jsonDeserialize(json, object);
}

QVariantMap QParseJsonSerializer::serialize(QObject *data)
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
                auto it = value.value<QSequentialIterable>();
                for (const auto& v : it) {
                    if(auto o = qvariant_cast<QObject*>(v)) {
                        list << serialize(o);
                    }
                }
            }
            else {
                list = QVariantList(value.toList());
            }
            map[propertyName] = list;
            //qDebug() << list;
        }
        else if(auto o = qvariant_cast<QObject*>(value)){
            //qDebug() << "___Other Object___";
            map[propertyName] = serialize(o);
            //qDebug() << "__________________";
        }
        else {
            //qDebug() << propertyName << value;
            map[propertyName] = value;
        }
    }
    return map;
}

template <typename T, typename std::enable_if<std::is_base_of<QObject, T>::value>::type*>
T* QParseJsonSerializer::deserialize(const QVariantMap& data, T *object) {
    if(!object) {
        return object;
    }

    for(auto i = data.constBegin(); i != data.constEnd(); ++i) {
        auto name = i.key().toUtf8();
        auto value = i.value();
        auto type = value.type();
        if(type == QVariant::List) {
            auto property = object->property(name);
            auto className = property.typeName();
            //qDebug() << className;
            //QVariantList variantList;
            QRegularExpression regex("<(.*)>");
            auto match = regex.match(className);
            auto classObjectName = match.captured(1);
            auto type = QMetaType::type(classObjectName.toUtf8());
            auto variantList = object->property(name).toList();
            for (const auto& e : value.toList()) {
                if(e.type() == QVariant::Map)  {
                    auto childMetaObject = QMetaType::metaObjectForType(type);
                    auto childObject = childMetaObject->newInstance();
                    deserialize(e.toMap(), childObject);
                    // TODO: not working...
                    variantList.append(QVariant::fromValue(childObject));
                }
                else {
                    variantList.append(e);
                }
            }
            //auto metaObject = object->metaObject();
            //auto p = metaObject->property(metaObject->indexOfProperty(name));
            qDebug() << "Adding" << name << "variantList" << variantList;
            //qDebug() << p.write(object, variantList);
            object->setProperty(name, variantList);


        }
        else if(type == QVariant::Map) {
            auto property = object->property(name);
            auto className = property.typeName();
            auto type = QMetaType::type(className);
            auto childMetaObject = QMetaType::metaObjectForType(type);
            auto childObject = childMetaObject->newInstance();
            object->setProperty(name, QVariant::fromValue(deserialize(value.toMap(), childObject)));
        }
        else {
            object->setProperty(name, value);
        }
    }

    return object;
}

QString QParseJsonSerializer::getTypeName(QString propertyName, QObject *object)
{
    auto metaObject = object->metaObject();
    auto metaProperty = metaObject->property(metaObject->indexOfProperty(propertyName.toUtf8()));
    return metaProperty.typeName();
}
