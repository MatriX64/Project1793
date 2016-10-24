#ifndef MODULEMANAGER_1793_H
#define MODULEMANAGER_1793_H

#include "module_1793.h"
#include "name_codes_1793.h"
#include "wps_attack_module.h"

#include <QDir>
#include <QObject>
#include <QString>
#include <QTextCodec>
#include <QProcess>

#include <QDebug>

class ModuleManager_1793 : public QObject
{
    Q_OBJECT
public:
    QDir *app_dir;

public:
    ModuleManager_1793();
    ~ModuleManager_1793();

    void start();

public: //modules
    WPS_Attack_module *wps_attack_module;

private:
     void check_paths();
     void check_libs();
     void add_modules();
     void delete_modules();

signals:
    void send_log_file(int, const QString&);
    void quit_critical_sender();
};

#endif // MODULEMANAGER_1793_H
