/*
 * Copyright (c) 2016,2017 sanmira32 <matrix3sai@gmail.com>
 *
 *  This file is part of Project1793.
 *
 *  Project1793 is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Project1793 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Project1793.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "interfacesmodel.h"

InterfacesModel::InterfacesModel(QObject *parent) : QAbstractListModel(parent)
{

}

void InterfacesModel::addInterface(const QString &interface)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    interfacesList << interface;
    endInsertRows();
}

void InterfacesModel::clearList()
{
    beginResetModel();
    interfacesList.clear();
    endResetModel();
}

int InterfacesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return interfacesList.count();
}

QVariant InterfacesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == InterfaceName)
        return interfacesList.at(index.row());
    return QVariant();
}

QHash<int, QByteArray> InterfacesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[InterfaceName] = "name";
    return roles;
}
