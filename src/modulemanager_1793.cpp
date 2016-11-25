#include "include/modulemanager_1793.h"

ModuleManager_1793::ModuleManager_1793(QQmlApplicationEngine *engine, QObject *parent) : QObject(parent),
                                                                                         moduleController(engine, this)
{

}

ModuleManager_1793::~ModuleManager_1793()
{
    delete_modules();
    Logger_1793::write_log_file(LogInfoMsg, "Менеджер модулей уничтожен");
}

void ModuleManager_1793::start()
{
    Logger_1793::write_log_file(LogInfoMsg, "Менеджер модулей запущен");

    process_modules();

    moduleController.start_modules();
}

void ModuleManager_1793::process_modules()
{
    moduleController.add_module(&wps_attack_module);
    moduleController.add_module(&dummy_module);
}

void ModuleManager_1793::delete_modules()
{
    //code for release allocated module memory
}
