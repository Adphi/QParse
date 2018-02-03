/*****************************************************************************
 *
 * QParseFileManager.cpp
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
#include <QMimeDatabase>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include "QParse.h"
#include "QParseFileManager.h"
#include "QParseAuth.h"

QByteArray QParseFileManager::FILE = "/files";
QParseFileManager *QParseFileManager::sInstance = nullptr;

QParseFileManager::QParseFileManager(QObject *parent) : QObject(parent)
{
    mManager = new QNetworkAccessManager(this);
}
void QParseFileManager::upload(const QString& filePath) const
{
    auto url = QUrl(filePath);
    QFile file(url.toLocalFile());
    QString fileName = url.fileName();
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open the file:" << file.fileName();
        return;
    }
    upload(fileName, file.readAll());
    file.close();
}

void QParseFileManager::remove(const QParseFile& file)
{
    auto *parse = QParse::getInstance();
    if(parse->masterKey().isNull()) {
        qDebug() << "Only available with Parse master key";
        return;
    }
    if(file.name().isNull() || file.name().isEmpty()) {
        qDebug() << "Missing File Name";
        return;
    }
    auto request = parse->request(FILE + "/" +file.name().toUtf8());
    request.setRawHeader(QParse::MASTER_KEY, parse->masterKey());
    auto reply = mManager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, [&, reply](){
        if(reply->error()) {
            qDebug() << reply->errorString();
            qDebug() << reply->readAll();
            return;
        }
        qDebug() << reply->readAll();
        emit removeFinished();
    });
}

QParseFileManager* QParseFileManager::getInstance() {
    if(!sInstance) {
        sInstance = new QParseFileManager(QParse::getInstance());
    }
    return sInstance;
}

void QParseFileManager::upload(const QString &name, const QByteArray &data) const
{
    QString token = QParseAuth::getInstance()->token();
    QMimeDatabase db;
    auto request = QParse::getInstance()->request(FILE + "/" + name.toUtf8());
    request.setRawHeader(QParse::SESSION_TOKEN, token.toUtf8());

    request.setHeader(QNetworkRequest::ContentTypeHeader, db.mimeTypeForUrl(QUrl(name)).name());
    qDebug() << "Sending File" << name << "(type:" << db.mimeTypeForUrl(QUrl(name)).name() <<")" << data.size() << "bytes";
    auto reply = mManager->post(request, data);
    connect(reply, &QNetworkReply::finished, [&, reply]() {
        if(reply->error()) {
            qDebug() << reply->errorString();
            qDebug() << reply->readAll();
            return;
        }
        QJsonDocument doc = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
        QJsonObject json = doc.object();
        QString name = json["name"].toString();
        QUrl url = QUrl(json["url"].toString());
        QParseFile parseFile(name, url);
        qDebug() << "Upload Success File:" << name << "Url:" << url;
        reply->deleteLater();
        emit uploadFinished(&parseFile);
    });
}
