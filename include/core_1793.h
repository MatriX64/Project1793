#ifndef CORE_1793_H
#define CORE_1793_H

#include <QGuiApplication>
#include <QThread>
#include <QEventLoop>

#include "modulemanager_1793.h"
#include "model_1793.h"
#include "name_codes_1793.h"
#include "logger_1793.h"

#include <QDebug>

class Core_1793 : public QObject
{
    Q_OBJECT
public:
    Core_1793();
    ~Core_1793();

    void start();

private:
    Logger_1793 *logger;
    Model_1793 *model;
    ModuleManager_1793 *moduleManager;
    QQmlApplicationEngine *mainView;
    QQmlApplicationEngine *splashView;
    QQmlApplicationEngine *fatalMessage;

public slots:
    void terminate_critical();
};

#endif // CORE_1793_H
