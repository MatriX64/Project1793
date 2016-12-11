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

#ifndef CORE_1793_H
#define CORE_1793_H

#include <QCoreApplication>
#include <QThread>
#include <QEventLoop>
#include <QQuickWindow>

#include "modulemanager_1793.h"
#include "app_data/model_1793.h"
#include "logger_1793.h"
#include "initializer_1793.h"

#include <QDebug>

class Core_1793 : public QObject
{
    Q_OBJECT
public:
    Core_1793(QObject *parent = 0);
    ~Core_1793();

    void start();

private:
    QQmlApplicationEngine* mainView;
    Model_1793* model;
    Initializer_1793* initializer;
    ModuleManager_1793* moduleManager;


private slots:
    void terminate_crirical();
};

#endif // CORE_1793_H
