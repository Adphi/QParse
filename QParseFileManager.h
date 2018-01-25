/*****************************************************************************
 *
 * QParseFileManager.h
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
#ifndef QPARSEFILEMANAGER_H
#define QPARSEFILEMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include "QParseFile.h"

class QParseFileManager : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE static QParseFileManager* getInstance();
    Q_INVOKABLE void upload(const QString& filePath) const;
    Q_INVOKABLE void upload(const QString& name, const QByteArray& data) const;
    Q_INVOKABLE void remove(const QParseFile& file) const;
signals:
    void uploadFinished(QParseFile *file) const;
    void removeFinished();

public slots:

private:
    explicit QParseFileManager(QObject *parent = nullptr);
    static QParseFileManager *sInstance;
    QNetworkAccessManager *mManager;
    // Path
    static QByteArray FILE;
};

#endif // QPARSEFILEMANAGER_H
