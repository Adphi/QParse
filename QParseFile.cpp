/*****************************************************************************
 *
 * QParseFile.cpp
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
#include "QParseFile.h"

#include "QParseAuth.h"
#include <QMimeDatabase>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

QByteArray QParseFile::FILE = "/files";

QParseFile::QParseFile(QObject *parent) : QObject(parent)
{
}

QParseFile::QParseFile(const QString &name, const QByteArray &url, QObject *parent) :
    QObject(parent), mName(name), mUrl(url)
{

}

void QParseFile::upload(const QString& filePath)
{
    mManager = new QNetworkAccessManager(this);
    QMimeDatabase db;
    QFile file(filePath);
    QString fileName = QUrl(filePath).fileName();
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open the file:" << file.fileName();
        return;
    }
    QString token = QParseAuth::getInstance()->token();
    auto request = QParse::getInstance()->request(FILE + "/" + fileName.toUtf8());
    request.setRawHeader(QParse::SESSION_TOKEN, token.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, db.mimeTypeForUrl(QUrl(filePath)).name());
    qDebug() << "Sending File" << fileName << "(type:" << db.mimeTypeForUrl(QUrl(filePath)).name() <<")" << file.size() << "bytes";
    mManager->post(request, file.readAll());
    connect(mManager, &QNetworkAccessManager::finished, [&](QNetworkReply* reply) {
        if(reply->error()) {
            qDebug() << reply->errorString();
            qDebug() << reply->readAll();
            return;
        }
        QJsonDocument doc = QJsonDocument::fromJson(QString(reply->readAll()).toUtf8());
        QJsonObject json = doc.object();
        mName = json["name"].toString();
        mUrl = json["url"].toString().toUtf8();
        qDebug() << "Upload Success File:" << mName << "Url:" << mUrl;
        reply->deleteLater();
        emit uploadFinished();
    });
    file.close();
}

QString QParseFile::name() const
{
    return mName;
}

void QParseFile::setName(const QString &name)
{
    mName = name;
}

QByteArray QParseFile::url() const
{
    return mUrl;
}

void QParseFile::setUrl(const QByteArray &url)
{
    mUrl = url;
}
