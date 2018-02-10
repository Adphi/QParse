/*****************************************************************************
 *
 * QParseObjectManager.cpp
 *
 * Created: 23 2018 by Philippe-Adrien
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
#include "QParseObjectManager.h"
#include <QParse.h>
#include <QNetworkReply>
#include <QtPropertySerializer.h>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMimeDatabase>
#include <QParseAuth.h>
#include "CustomObject.h"

QByteArray QParseObjectManager::OBJECT = "/classes";

QParseObjectManager *QParseObjectManager::sInstance = nullptr;

QParseObjectManager::QParseObjectManager(QObject *parent) : QObject(parent)
{
    mManager = new QNetworkAccessManager(this);
}

QParseObjectManager *QParseObjectManager::getInstance()
{
    if(!sInstance) {
        sInstance = new QParseObjectManager(QParse::getInstance());
    }
    return sInstance;
}

void QParseObjectManager::save(QParseObject *object)
{
    if( !object->objectId().isEmpty()) {
        qDebug() << "Object already saved. Calling update() instead";
        object->update();
        return;
    }

//    auto objectData = QJsonDocument(object->serialize());

    QString className = object->metaObject()->className();
    auto request = QParse::getInstance()->request(OBJECT + "/" + className.toUtf8());
    request.setRawHeader(QParse::SESSION_TOKEN, QParseAuth::getInstance()->token().toUtf8());
    // TODO serialize
    QVariantMap data = QtPropertySerializer::serialize(object);
    auto objectData = QJsonDocument::fromVariant(data);
    qDebug() << objectData;
    QMimeDatabase db;
    request.setHeader(QNetworkRequest::ContentTypeHeader, db.mimeTypeForData(objectData.toBinaryData()).name());
    auto reply = mManager->post(request, objectData.toJson());
    connect(reply, &QNetworkReply::finished, [&, reply, object](){
        if(reply->error()) {
            qDebug() << reply->errorString();
            qDebug() << reply->readAll();
            return;
        }
        QJsonDocument doc = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
        const QJsonObject json = doc.object();
        //QtPropertySerializer::deserialize(object, json.toVariantMap());
//        object->deserialize(json);

        // TODO: deserialize
        reply->deleteLater();
        qDebug() << "Object saved" << *object;
        emit saved(object);
    });
}

void QParseObjectManager::update(QParseObject *object)
{
    QString className = object->metaObject()->className();
    auto request = QParse::getInstance()->request(OBJECT + "/" + className.toUtf8() + "/" + object->objectId().toUtf8());
    request.setRawHeader(QParse::SESSION_TOKEN, QParseAuth::getInstance()->token().toUtf8());

    // TODO: serialize
//    auto data = object->serialize();
    QVariantMap data = QtPropertySerializer::serialize(object);
    auto objectData = QJsonDocument::fromVariant(data);

    QMimeDatabase db;
    request.setHeader(QNetworkRequest::ContentTypeHeader, db.mimeTypeForData(objectData.toBinaryData()).name());
    auto reply = mManager->put(request, objectData.toJson());
    connect(reply, &QNetworkReply::finished, [&, reply, object](){
        if(reply->error()) {
            qDebug() << reply->errorString();
            qDebug() << reply->readAll();
            return;
        }
        QJsonDocument doc = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
        const QJsonObject json = doc.object();
        qDebug() << json;

        // TODO: deserialize
        QtPropertySerializer::deserialize(object, json.toVariantMap());
//        object->deserialize(json);
        reply->deleteLater();
        qDebug() << "Object Updated" << *object;
        emit updated(object);
    });
}

void QParseObjectManager::remove(QParseObject *object)
{
    QString className = object->metaObject()->className();
    QString id = object->objectId();
    auto request = QParse::getInstance()->request(OBJECT + "/" + className.toUtf8() + "/" + id.toUtf8());
    auto reply = mManager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, [&, reply, object](){
        if(reply->error()) {
            qDebug() << reply->errorString();
            qDebug() << reply->readAll();
            return;
        }
       qDebug() << reply->readAll();
       object->setObjectId("");
       object->setCreatedAt(QDateTime());
       object->setUpdatedAt(QDateTime());
       emit removed();
    });
}
