#ifndef MODULEMANAGER_1793_H
#define MODULEMANAGER_1793_H

#include <QDir>
#include <QFile>
#include <QObject>
#include <QString>
#include <QTextCodec>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>

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

    QDir app_dir;
    Model_1793 *mainModel;
    void start();

public: //modules
    WPS_Attack_module *wps_attack_module;
    WPS_Attack_module *wps_attack_module2;
    WPS_Attack_module *wps_attack_module3;

private:
     void check_paths();
     void check_libs();
     void add_modules();
     void set_modules();
     void delete_modules();

signals:
    void send_log_file(int, const QString&);
    void quit_critical_sender();
};

#endif // MODULEMANAGER_1793_H
