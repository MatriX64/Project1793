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

#ifndef INTERFACESMODEL_H
#define INTERFACESMODEL_H

#include <QAbstractListModel>
#include <QList>

#include <QDebug>

class InterfacesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit InterfacesModel(QObject *parent = 0);

    enum InterfaceRoles {
        InterfaceName = Qt::UserRole + 1
    };

    void addInterface(const QString& interface);
    void clearList();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<QString> interfacesList;

signals:

public slots:
};

#endif // INTERFACESMODEL_H
