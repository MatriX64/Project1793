/*
 * Copyright (c) 2016, MatriXSan <matrix3sai@gmail.com>
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

#include "wpsnetworklistmodel.h"


WPSNetworkListModel::WPSNetworkListModel(QObject *parent) : QAbstractListModel(parent)
{

}

void WPSNetworkListModel::addNetwork(const Network &network)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    networkList << network;
    endInsertRows();
}

void WPSNetworkListModel::clearList()
{
    beginResetModel();
    networkList.clear();
    endResetModel();
}

int WPSNetworkListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return networkList.count();
}

QVariant WPSNetworkListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= networkList.count())
        return QVariant();
    const Network &network = networkList[index.row()];
    if (role == NetworkName)
        return network.name();
    else if (role == NetworkMac)
        return network.mac();
    return QVariant();
}

QHash<int, QByteArray> WPSNetworkListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NetworkName] = "name";
    roles[NetworkMac] = "mac";
    return roles;
}
