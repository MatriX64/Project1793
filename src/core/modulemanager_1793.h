#ifndef MODULEMANAGER_1793_H
#define MODULEMANAGER_1793_H

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QCoreApplication>

#include "logger_1793.h"
#include "app_data/model_1793.h"
#include "name_codes_1793.h"
#include "app_data/model_1793.h"

//modules
#include "../modules/wps_attack_module.h"
#include "../modules/dummymodule.h"

#include <QDebug>

class ModuleManager_1793 : public QObject
{
    Q_OBJECT
public:
    ModuleManager_1793(QQmlApplicationEngine *engine, QObject *parent);
    ~ModuleManager_1793();
private:
    Module_1793 moduleController;

public:
    void start();

public: //modules
    WPS_Attack_module wps_attack_module;
    DummyModule dummy_module;

private:
    void process_modules();
    void delete_modules();

signals:
    void critical_error();
};

#endif // MODULEMANAGER_1793_H
