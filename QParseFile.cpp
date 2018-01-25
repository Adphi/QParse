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

#include "QParseFileManager.h"
#include <QFile>

QParseFile::QParseFile(QObject *parent) : QObject(parent)
{
}

QParseFile::QParseFile(const QString &name, const QUrl &url, QObject *parent) :
        QObject(parent), mName(name), mUrl(url)
{

}

void QParseFile::upload(const QString& filePath)
{
    auto *fileManager = QParseFileManager::getInstance();
    fileManager->upload(filePath);
    // TODO: connect to uploadFinished
    connect(fileManager, &QParseFileManager::uploadFinished, [&](QParseFile *file){
        mName = file->name();
        mUrl = file->url();
        emit uploadFinished();
    });
}

void QParseFile::remove()
{
    auto fileManager = QParseFileManager::getInstance();
    fileManager->remove(*this);
    connect(fileManager, &QParseFileManager::removeFinished, [&](){
        emit removed();
    });
}



QString QParseFile::name() const
{
    return mName;
}

void QParseFile::setName(const QString &name)
{
    mName = name;
}

QUrl QParseFile::url() const
{
    return mUrl;
}

void QParseFile::setUrl(const QUrl &url)
{
    mUrl = url;
}

void QParseFile::upload(const QString &name, const QByteArray data) {
    auto *fileManager = QParseFileManager::getInstance();
    fileManager->upload(name, data);
    // TODO: connect to uploadFinished
    connect(fileManager, &QParseFileManager::uploadFinished, [&](QParseFile *file){
        mName = file->name();
        mUrl = file->url();
        emit uploadFinished();
    });
}
