/*****************************************************************************
 *
 * QParseFile.h
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
#ifndef QPARSEFILE_H
#define QPARSEFILE_H

#include <QObject>

class QParseFile : public QObject
{
    Q_OBJECT
public:
    explicit QParseFile(QObject *parent = nullptr);
    QParseFile(const QString& name, const QByteArray& url, QObject *parent = nullptr);
private:
    QString mName;
    QByteArray mUrl;
};

#endif // QPARSEFILE_H
