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

#ifndef NETWORKLISTMODEL_H
#define NETWORKLISTMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "network.h"

class WPSNetworkListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WPSNetworkListModel(QObject *parent = 0);

public:
    enum NetworkRoles {
        NetworkName = Qt::UserRole + 1,
        NetworkMac
    };

    void addNetwork(const Network &network);
    void clearList();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Network> networkList;
};

#endif // NETWORKLISTMODEL_H
