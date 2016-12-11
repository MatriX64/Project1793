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

#include "modulemanager_1793.h"

ModuleManager_1793::ModuleManager_1793(QObject *parent) : QObject(parent)
{

}

ModuleManager_1793::~ModuleManager_1793()
{
    moduleController.terminate_modules();
    Logger_1793::write_log_file(LogInfoMsg, "Module manager destroyed");
}

void ModuleManager_1793::start()
{
    Logger_1793::write_log_file(LogInfoMsg, "Module manager started");

    process_modules();

    moduleController.start_modules();
}

void ModuleManager_1793::process_modules()
{
    moduleController.add_module(&wps_attack_module);
    moduleController.add_module(&dummy_module);
}
