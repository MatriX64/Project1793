#include "include/app_controller_1793.h"

QGuiApplication *AppController_1793::application;

AppController_1793::AppController_1793(QObject *parent) : QObject(parent)
{

}

AppController_1793::~AppController_1793()
{
    delete (application);
}

void AppController_1793::terminate_normal()
{
    qDebug() << "Terminated normal";
    application->exit(0);
}

void AppController_1793::terminate_critical()
{
    QQmlApplicationEngine fatal_message;
    fatal_message.load("/home/san/Qt/Projects/Project1793/qml/fatal_message.qml");

    connect(application, SIGNAL(lastWindowClosed()), application, SLOT(quit()));
    QObject *item = fatal_message.rootObjects().first();
    connect(item, SIGNAL(quit_signal()), application, SLOT(quit()));

    application->exec();

    qDebug() << "Terminated critical";
    Logger_1793::write_log_file(LogInfoMsg, "Программа аварийно завершена\n");
    delete (application);
    std::exit(-1);
}
