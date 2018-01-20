/*****************************************************************************
 *
 * Utils.h
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
#ifndef UTILS_H
#define UTILS_H

#include <QDebug>
#include <QMetaProperty>

#include <vector>
#include <utility>
#include <algorithm>

static void dump_props(QObject *o)
{
  auto mo = o->metaObject();
  qDebug() << "## Properties of" << o << "##";
  do {
    qDebug() << "### Class" << mo->className() << "###";
    std::vector<std::pair<QString, QVariant> > v;
    v.reserve(mo->propertyCount() - mo->propertyOffset());
    for (int i = mo->propertyOffset(); i < mo->propertyCount();
          ++i)
      v.emplace_back(mo->property(i).name(),
                     mo->property(i).read(o));
    std::sort(v.begin(), v.end());
    for (auto &i : v)
      qDebug() << i.first << "=>" << i.second;
  } while ((mo = mo->superClass()));
}

#endif // UTILS_H
