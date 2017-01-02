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

#ifndef MODEL_1793_H
#define MODEL_1793_H

#include <QQmlApplicationEngine>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QQmlContext>
#include <QVariant>

#include "wpsnetworklistmodel.h"
#include "interfacesmodel.h"

#include <QDebug>

struct SystemData_1793
{
    QByteArray* mainViewComponentData;
};

class Model_1793 : public QObject
{
    Q_OBJECT
public:
    Model_1793(QObject* parent = 0);
    ~Model_1793();

    SystemData_1793 systemData;

private: //modules data
    WPSNetworkListModel networksList;
    InterfacesModel interfacesList;


public slots: //modules data slots
    void add_new_network(const Network &network);
    void clear_WPS_networks_list();
    void add_new_interface(const QString &interface);
    void clear_interfaces_list();
};

#endif // MODEL_1793_H
