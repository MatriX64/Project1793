#include "include/wps_attack_module.h"

WPS_Attack_module::WPS_Attack_module(QObject *parent) : QObject(parent)
{
    connect(Module_1793::qmlSignals, SIGNAL(qmlScream()), this, SLOT(qmlSignalHandler()));
}

WPS_Attack_module::~WPS_Attack_module()
{

}


void WPS_Attack_module::qmlSignalHandler()
{
    qDebug() << "Current thread:" << QThread::currentThread();
}
