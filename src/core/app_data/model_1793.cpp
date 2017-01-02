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

#include "model_1793.h"
#include "../windowsmanager_1793.h"

Model_1793::Model_1793(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<Network>();

    systemData.mainViewComponentData = new QByteArray;

    WindowsManager_1793::setContextProperty("wpsListModel", QVariant::fromValue(&networksList));
    WindowsManager_1793::setContextProperty("interfacesListModel", QVariant::fromValue(&interfacesList));
}

Model_1793::~Model_1793()
{
    delete systemData.mainViewComponentData;
}

void Model_1793::add_new_network(const Network &network)
{
    networksList.addNetwork(network);
}

void Model_1793::clear_WPS_networks_list()
{
    networksList.clearList();
}

void Model_1793::add_new_interface(const QString &interface)
{
    interfacesList.addInterface(interface);
}

void Model_1793::clear_interfaces_list()
{
    interfacesList.clearList();
}
