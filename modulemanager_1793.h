#ifndef MODULEMANAGER_1793_H
#define MODULEMANAGER_1793_H

#include "name_codes_1793.h"

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

private:
     void check_paths();
     void check_libs();

signals:
    void send_log_file(int, const QString&);
    void critical_sender();
};

#endif // MODULEMANAGER_1793_H
