/*****************************************************************************
 *
 * QParseRequest.h
 *
 * Created: 25 2018 by Philippe-Adrien
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
#ifndef QPARSEQUERY_H
#define QPARSEQUERY_H

#include <QObject>
#include <QAbstractParseObject.h>

//template <typename T, typename std::enable_if<std::is_base_of<QAbstractParseObject, T>::value>::type* = nullptr>
class QParseQuery : public QObject
{
    Q_OBJECT
public:
    explicit QParseQuery(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QPARSEQUERY_H
