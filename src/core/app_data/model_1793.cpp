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

#include "model_1793.h"

Model_1793* Model_1793::model;

QQmlApplicationEngine* Model_1793::engineHandler;
QMap<QString,QString>  Model_1793::qmlTabView;
QList<QString>         Model_1793::modulesList;

Model_1793::Model_1793(QQmlApplicationEngine *engine, QObject *parent) : QObject(parent)
{
    qRegisterMetaType<Network>();
    model = this;

    Model_1793::engineHandler = engine;
    engineHandler->rootContext()->setContextProperty("wpsListModel", QVariant::fromValue(&networksList));
    engineHandler->rootContext()->setContextProperty("interfacesListModel", QVariant::fromValue(&interfacesList));
}

Model_1793::~Model_1793()
{
    Logger_1793::write_log_file(LogInfoMsg, "Model destroyed");
}

void Model_1793::start()
{
    Logger_1793::write_log_file(LogInfoMsg, "Model started");
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
