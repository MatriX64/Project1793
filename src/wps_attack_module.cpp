#include "include/wps_attack_module.h"

WPS_Attack_module::WPS_Attack_module(const QString& moduleName, const QString &fileName) : Module_1793(moduleName, fileName)
{
    qDebug() << mainModel->str;
    mainModel->str.append(" Hey)");
    qDebug() << mainModel->str;
}

WPS_Attack_module::~WPS_Attack_module()
{

}
