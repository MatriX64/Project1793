#ifndef MODULEMANAGER_1793_H
#define MODULEMANAGER_1793_H

#include <QFile>
#include <QObject>
#include <QString>
#include <QTextCodec>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>

#include "logger_1793.h"
#include "model_1793.h"
#include "name_codes_1793.h"
#include "wps_attack_module.h"
#include "datacommunicator.h"

#include <QDebug>

class ModuleManager_1793 : public DataCommunicator
{
    Q_OBJECT
public:
    ModuleManager_1793();
    ~ModuleManager_1793();

    Model_1793 *mainModel;

public slots:
    void startLaunchRoutine();

public: //modules
    WPS_Attack_module *wps_attack_module;
    WPS_Attack_module *wps_attack_module2;
    WPS_Attack_module *wps_attack_module3;

private:
     bool check_paths();
     bool check_libs();
     void add_modules();
     void set_modules();
     void delete_modules();

signals:
     void finishLaunchRoutine();
     void critical_error();
};

#endif // MODULEMANAGER_1793_H
