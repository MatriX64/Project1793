#include "include/wps_attack_module.h"

WPS_Attack_module::WPS_Attack_module(QObject *parent) : QObject(parent)
{
    connect(Module_1793::qmlRootObjectHandler, SIGNAL(signal_Refresh_WPS_list()), this, SLOT(refresh_WPS_networks_list()));
    connect(this, SIGNAL(add_new_WPS_network(Network)), Model_1793::model, SLOT(add_new_network(Network)));

}

WPS_Attack_module::~WPS_Attack_module()
{

}


void WPS_Attack_module::refresh_WPS_networks_list()
{
    emit add_new_WPS_network("Network " + QString::number(number));
    number++;

    /*QObject *temp = Module_1793::qmlRootObjectHandler->findChild<QObject*>("wpsAttackModule");
    QMetaObject::invokeMethod(temp, "stop_refreshing_WPS_list");*/
}
