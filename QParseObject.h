/*****************************************************************************
 *
 * QParseObject.h
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
#ifndef QPARSEOBJECT_H
#define QPARSEOBJECT_H

#include <QObject>
#include <QDateTime>

class QParseObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString objectId READ objectId WRITE setObjectId NOTIFY objectIdChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt NOTIFY updatedAtChanged)

public:
    explicit QParseObject(QObject *parent = nullptr);

    QString objectId() const;
    void setObjectId(const QString &objectId);

    QDateTime updatedAt() const;
    void setUpdatedAt(const QDateTime &updatedAt);

    QDateTime createdAt() const;
    void setCreatedAt(const QDateTime &createdAt);

signals:
    void objectIdChanged();
    void createdAtChanged();
    void updatedAtChanged();

public slots:

protected:
    QString mObjectId;
    QDateTime mUpdatedAt;
    QDateTime mCreatedAt;
};

#endif // QPARSEOBJECT_H
