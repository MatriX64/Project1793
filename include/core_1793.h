#ifndef CORE_1793_H
#define CORE_1793_H

#include <QGuiApplication>
#include "modulemanager_1793.h"
#include "model_1793.h"
#include "name_codes_1793.h"

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QFile>

#include <QDebug>

class Core_1793 : public QObject
{
    Q_OBJECT
public:
    Core_1793(int argc, char *argv[]);
    ~Core_1793();

public:
    QGuiApplication *application;

protected:
    void open_log_file();

private:
    ModuleManager_1793 *module_manager;
    Model_1793 *model;

    QFile *m_logFile;

public slots:
    void write_log_file(int, const QString&);
    void quit_critical_receiver();
    void quit_normal_receiver();
    void quit_critical();

};

#endif // CORE_1793_H
