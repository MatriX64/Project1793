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

#include <unistd.h>

#include "core/app_data/model_1793.h"
#include "core/modulesmanager_1793.h"
#include "core/windowsmanager_1793.h"

#include "modules/wps_attack_module.h"
#include "modules/dummymodule.h"
#include "modules/handshake_attack_module.h"

int main(int argc, char *argv[])
{
    QGuiApplication application(argc, argv);

    QQmlApplicationEngine qmlEngine;
    WindowsManager_1793 windowsManager;
    windowsManager.initialize(qmlEngine);

    bool checkingRootStatus = true;
    if (getuid() != 0)
    {
        WindowsManager_1793::show_notification_critical("Error. Please, run this program as root");
        checkingRootStatus = false;
    }

    Model_1793 model;
    ModulesManager_1793 modulesManager;

    if (checkingRootStatus == true)
    {
        modulesManager.add_new_module(new WPS_Attack_module(),     "WPS_Attack",     "password_attacks|wep/wpa/wpa2_attacks|WPS_attack");
        modulesManager.add_new_module(new RogueAP_Attack_module(), "Handshake_Attack", "password_attacks|wep/wpa/wpa2_attacks|Handshake_Attack");
        modulesManager.add_new_module(new DummyModule(),           "DummyQML",       "password_attacks|test_module");

        QByteArray mainViewData = modulesManager.set_modules();
        windowsManager.load_main_view(mainViewData);
        modulesManager.start_modules(&model);
    }

    application.exec();
}
