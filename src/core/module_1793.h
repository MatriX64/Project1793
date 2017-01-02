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

#ifndef MODULE_1793_H
#define MODULE_1793_H

#include <QString>
#include <QGuiApplication>
#include <QRegularExpression>
#include <QDebug>
#include <QObject>
#include <QPointer>
#include <QThread>

#include "app_data/model_1793.h"
#include "windowsmanager_1793.h"

class Module_1793 : public QObject
{
    Q_OBJECT
public:
    explicit Module_1793(QObject *parent = 0);
    ~Module_1793();

public:
    void initialize_module(Model_1793* model);

protected:
    Model_1793* modelData;

public slots:
    virtual void start_module();
    virtual void terminate_module();
};

#endif // MODULE_1793_H
