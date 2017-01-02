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

#include "dummymodule.h"

DummyModule::DummyModule(QObject *parent) : Module_1793(parent)
{

}

DummyModule::~DummyModule()
{

}

void DummyModule::start_module()
{
    //WindowsManager_1793::show_notification_warning("DummyModule started");

    QObject* moduleRootObject = WindowsManager_1793::getQmlObject("dummyModule");

    connect(moduleRootObject, SIGNAL(signalDummy()), this, SLOT(qmlSignalHandler()));

    qDebug() << "DummyModule started";
}

void DummyModule::terminate_module()
{
    qDebug() << "Dummy termination";
}

void DummyModule::qmlSignalHandler()
{
    qDebug() << "Current thread:" << QThread::currentThread();
}
