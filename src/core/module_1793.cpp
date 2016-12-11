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

#include "module_1793.h"

QObject*               Module_1793::qmlRootObjectHandler;

Module_1793::Module_1793(QObject *parent) : QObject(parent)
{
    qmlRootObjectHandler = Model_1793::engineHandler->rootObjects().first();
}

Module_1793::~Module_1793()
{
    delete (modulesList);
    delete (threadList);
}

void Module_1793::add_module(QObject *moduleObject)
{
    modulesList->append(moduleObject);
    threadList->append(new QThread(this));
}

void Module_1793::start_modules()
{
    for (int i = 0; i < modulesList->count(); i++)
    {
        modulesList->at(i)->moveToThread(threadList->at(i));
        connect(threadList->at(i), SIGNAL(started()), modulesList->at(i), SLOT(initialize()));
        threadList->at(i)->start();
    }
}

void Module_1793::terminate_modules()
{
    for (int i = 0; i < modulesList->count(); i++)
    {
        connect(this, SIGNAL(terminate_module_signal()), modulesList->at(i), SLOT(terminate()));
        emit terminate_module_signal();
        threadList->at(i)->quit();
        threadList->at(i)->wait(-1);
        delete (threadList->at(i));
    }
}
