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

#ifndef MODULESMANAGER_1793_H
#define MODULESMANAGER_1793_H

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>

#include "app_data/model_1793.h"
#include "module_1793.h"

#include <QDebug>

#define ModuleNotLoaded 100
#define ModuleWait 101
#define ModuleLoaded 102

class ModulesManager_1793 : public QObject
{
    Q_OBJECT
public:
    ModulesManager_1793(QObject *parent = 0);
    ~ModulesManager_1793();
public:
    Module_1793 moduleController;

public:
    void add_new_module(Module_1793* module, const QString& moduleName, const QString& modulePath);
    QByteArray set_modules();
    void start_modules(Model_1793* model);
    void terminate_modules();

private:
    QList<Module_1793*> modulesList;
    QList<QString> modulesNamesList;
    QMap<QString,QString> qmlTabView;
};

#endif // MODULESMANAGER_1793_H
