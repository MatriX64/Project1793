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

#ifndef WPS_ATTACK_MODULE_H
#define WPS_ATTACK_MODULE_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QStringList>
#include <QQmlComponent>
#include <QPointer>
#include <QProcess>
#include <QRegularExpression>

#include "../core/module_1793.h"

#define flag_interface_not_handling   0
#define flag_interface_WPS_refreshing 1
#define flag_interface_WPS_attack     2

class WPS_Attack_module : public QObject
{
    Q_OBJECT
public:
    explicit WPS_Attack_module(QObject* parent = 0);
    ~WPS_Attack_module();

private:
    QString monitorInterface = "";
    QString name = "";
    QString mac = "";
    int pixieState = 0;

    int currentInterfaceMode = flag_interface_not_handling;

    QPointer<QProcess> startWPSAttack;
    QPointer<QProcess> loadWPSLits;
    QPointer<QProcess> loadInterfacesList;
    QPointer<QProcess> switchInterfaceToMonitor;
    QPointer<QProcess> switchInterfaceToStation;
    QPointer<QProcess> checkAppsToKill;
    QPointer<QProcess> puttingInterfaceDown;
    QPointer<QProcess> puttingInterfaceUp;

    //service
    void append_new_message_to_std(const QVariant &data);

public slots:
    void initialize();
    void terminate();

    //refreshing interfaces list
    void refresh_interfaces_list();
    void handle_interfaces_info();
    void stop_refreshing_interfaces_list();

    //routine
    void start_working_with_interface(const QString& interface);
    void handle_switch_interface_to_monitor_data();
    void stop_switching_interface_to_monitor();
    void start_checking_apps_tokill();
    void handle_checking_apps_tokill_data();
    void start_putting_interface_down();
    void start_putting_interface_up();
    void switch_interface_to_station();
    void handle_switch_interface_to_station_data();
    void stop_switching_interface_to_station();
    void complete_routine();

    //refreshing networks with WPS list
    void refresh_WPS_networks_list(const QString& interface);
    void start_refreshing_WPS_list();
    void handle_refreshing_WPS_data();
    void stop_refreshing_WPS_list();

    //WPS_attack
    void WPS_attack(const QString& interface, const QString& essid, const QString& bssid,
                    const int pixie);
    void start_WPS_attack();
    void handle_WPS_attack_data();
    void stop_WPS_attack();
    void WPS_send_confirm();
    void complete_WPS_attack();

signals:
    void clear_interfaces_list_model();
    void clear_WPS_list_model();
    void add_new_WPS_network(const Network &network);
    void add_new_interface(const QString &interface);
};

#endif // WPS_ATTACK_MODULE_H
