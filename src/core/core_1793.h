#ifndef CORE_1793_H
#define CORE_1793_H

#include <QGuiApplication>
#include <QThread>
#include <QEventLoop>
#include <QQuickView>

#include "modulemanager_1793.h"
#include "app_data/model_1793.h"
#include "logger_1793.h"
#include "initializer_1793.h"

#include <QDebug>

class Core_1793 : public QObject
{
    Q_OBJECT
public:
    Core_1793(QGuiApplication *application, QObject *parent = 0);
    ~Core_1793();

    void start();

private:
    QGuiApplication *appHandler;
    QThread *launchThread;
    Logger_1793 *logger;
    Initializer_1793 *initializer;
    Model_1793 *model;
    ModuleManager_1793 *moduleManager;
    QQmlApplicationEngine *mainView;

private slots:
    void terminate_crirical();
};

#endif // CORE_1793_H
