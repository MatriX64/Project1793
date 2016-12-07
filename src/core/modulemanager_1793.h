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

#ifndef MODULEMANAGER_1793_H
#define MODULEMANAGER_1793_H

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QCoreApplication>

#include "logger_1793.h"
#include "app_data/model_1793.h"
#include "app_data/model_1793.h"

//modules
#include "../modules/wps_attack_module.h"
#include "../modules/dummymodule.h"

#include <QDebug>

class ModuleManager_1793 : public QObject
{
    Q_OBJECT
public:
    ModuleManager_1793(QQmlApplicationEngine *engine, QObject *parent);
    ~ModuleManager_1793();
public:
    Module_1793 moduleController;

public:
    void start();

public: //modules
    WPS_Attack_module wps_attack_module;
    DummyModule dummy_module;

private:
    void process_modules();
    void delete_modules();
};

#endif // MODULEMANAGER_1793_H
