#include "wps_attack_module.h"

WPS_Attack_module::WPS_Attack_module(QObject *parent) : QObject(parent)
{
    connect(Module_1793::qmlRootObjectHandler, SIGNAL(signal_Refresh_WPS_list(QString)), this, SLOT(refresh_WPS_networks_list(QString)));

    connect(Module_1793::qmlRootObjectHandler, SIGNAL(signal_Refresh_interfaces_list()), this, SLOT(refresh_interfaces_list()));
    connect(Module_1793::qmlRootObjectHandler, SIGNAL(signal_Stop_refreshing_WPS_list()), this, SLOT(stop_refreshing_WPS_list()));

    connect(this, SIGNAL(add_new_WPS_network(Network)), Model_1793::model, SLOT(add_new_network(Network)));
    connect(this, SIGNAL(add_new_interface(QString)), Model_1793::model, SLOT(add_new_interface(QString)));

    connect(this, SIGNAL(clear_WPS_list_model()), Model_1793::model, SLOT(clear_WPS_networks_list()));
    connect(this, SIGNAL(clear_interfaces_list_model()), Model_1793::model, SLOT(clear_interfaces_list()));
}

WPS_Attack_module::~WPS_Attack_module()
{

}

void WPS_Attack_module::startup_initialization()
{
    refresh_interfaces_list();
}

void WPS_Attack_module::refresh_interfaces_list()
{
    emit clear_interfaces_list_model();
    QProcess loadInterfacesList;
    loadInterfacesList.start("iw dev");
    QByteArray data;
    while (loadInterfacesList.waitForReadyRead(-1))
    {
        data.append(loadInterfacesList.readAll());
    }
    loadInterfacesList.waitForFinished();

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
    data.clear();
}

void WPS_Attack_module::refresh_WPS_networks_list(const QString &interface)
{
    //emit clear_WPS_list_model();
    monitorInterface = switch_interface_to_monitor(interface);

    loadWPSLits = new QProcess(this);
    connect(loadWPSLits, SIGNAL(readyRead()), this, SLOT(handle_refreshing_WPS_data()));
    loadWPSLits->start("wash -i " + monitorInterface);
}

void WPS_Attack_module::handle_refreshing_WPS_data()
{
    QByteArray data;
    data = loadWPSLits->readAll();
    append_new_message_to_std(QVariant("New data portion"));
    append_new_message_to_std(QVariant(data).toString());
}

QString WPS_Attack_module::switch_interface_to_monitor(const QString &interface)
{
    QString monitorInterface;
    QProcess startMonitor;
    startMonitor.start("airmon-ng check kill");
    QByteArray data;
    while (startMonitor.waitForReadyRead(-1))
    {
        data.append(startMonitor.readAll());
    }
    startMonitor.waitForFinished();
    append_new_message_to_std(QVariant(data));
    data.clear();

    startMonitor.start("airmon-ng start " + interface);
    while (startMonitor.waitForReadyRead(-1))
    {
        data.append(startMonitor.readAll());
    }
    startMonitor.waitForFinished();
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
    data.clear();

    qDebug() << monitorInterface;

    append_new_message_to_std(QVariant("Interface switched to monitor mode"));

    return monitorInterface;
}

void WPS_Attack_module::switch_interface_to_station()
{
    QByteArray data;
    QProcess stopMonitor;
    stopMonitor.start("airmon-ng stop " + monitorInterface);
    while (stopMonitor.waitForReadyRead(-1))
    {
        data.append(stopMonitor.readAll());
    }
    stopMonitor.waitForFinished();
    append_new_message_to_std(QVariant(data));
    append_new_message_to_std(QVariant("Interface switched to station mode"));
}

void WPS_Attack_module::stop_refreshing_WPS_list()
{
    if (loadWPSLits.isNull())
    {
        append_new_message_to_std(QVariant("Refreshin WPS list not running"));
        return;
    }
    else
    {
        append_new_message_to_std(QVariant("WPS list updated"));
        loadWPSLits->terminate();
        loadWPSLits.clear();
        switch_interface_to_station();
    }
}

void WPS_Attack_module::append_new_message_to_std(const QVariant& data)
{
    QPointer<QObject> moduleObject = Module_1793::qmlRootObjectHandler->findChild<QObject*>("wpsAttackModule");
    QMetaObject::invokeMethod(moduleObject, "append_stdout_text",
                              Q_ARG(QVariant, data));
    moduleObject.clear();
}
