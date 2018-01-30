/*****************************************************************************
 *
 * QParseObjectManager.h
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
#ifndef QPARSEOBJECTMANAGER_H
#define QPARSEOBJECTMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QAbstractParseObject.h>

class QParseObjectManager : public QObject
{
    Q_OBJECT
public:
    explicit QParseObjectManager(QObject *parent = nullptr);
    Q_INVOKABLE static QParseObjectManager* getInstance();

    Q_INVOKABLE void save(QAbstractParseObject *object);
    Q_INVOKABLE void update(QAbstractParseObject *object);
    Q_INVOKABLE void remove(QAbstractParseObject *object);

signals:
    void saved(QAbstractParseObject* parseObject);
    void updated(QAbstractParseObject* parseObject);
    void removed();

public slots:

private:
    static QParseObjectManager *sInstance;
    QNetworkAccessManager *mManager;

    // Path
    static QByteArray OBJECT;
};

#endif // QPARSEOBJECTMANAGER_H
