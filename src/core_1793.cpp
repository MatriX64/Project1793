#include "include/core_1793.h"

Core_1793::Core_1793()
{

}

Core_1793::~Core_1793()
{
    delete (moduleManager);
    delete (model);
    delete (mainView);

    Logger_1793::write_log_file(LogInfoMsg, "Программа завершена");

    delete (logger);
}

void Core_1793::start()
{
    logger = new Logger_1793;
    model = new Model_1793;
    moduleManager = new ModuleManager_1793;
    mainView = new QQmlApplicationEngine;
    splashView = new QQmlApplicationEngine;

    logger->initialize();
    model->start();

    splashView->load(QUrl("qrc:/qml/LauncherView.qml"));

    QEventLoop launchViewLoop;
    QThread *launchThread = new QThread;
    moduleManager->moveToThread(launchThread);
    connect(moduleManager, SIGNAL(finishLaunchRoutine()), &launchViewLoop, SLOT(quit()));
    connect(launchThread,  SIGNAL(started()),             moduleManager,   SLOT(startLaunchRoutine()));
    connect(moduleManager, SIGNAL(finishLaunchRoutine()), launchThread,    SLOT(quit()));
    connect(moduleManager, SIGNAL(finishLaunchRoutine()), launchThread,    SLOT(deleteLater()));
    connect(moduleManager, SIGNAL(finishLaunchRoutine()), &launchViewLoop, SLOT(quit()));
    connect(moduleManager, SIGNAL(finishLaunchRoutine()), splashView,      SLOT(deleteLater()));
    connect(moduleManager, SIGNAL(critical_error()),      launchThread,    SLOT(quit()));
    connect(moduleManager, SIGNAL(critical_error()),      launchThread,    SLOT(deleteLater()));
    connect(moduleManager, SIGNAL(critical_error()),      this,            SLOT(terminate_critical()));
    launchThread->start();
    launchViewLoop.exec();

    mainView->load(QUrl("qrc:/qml/main_view.qml"));
}

void Core_1793::terminate_critical()
{
    qDebug() << "here";
    fatalMessage = new QQmlApplicationEngine;
    fatalMessage->load(QUrl("qrc:/qml/fatal_message.qml"));
    QEventLoop wait;
    QObject *item = fatalMessage->rootObjects().first();
    connect(item, SIGNAL(quit_signal()), &wait, SLOT(quit()));
    wait.exec();

    qDebug() << "Terminated critical";
    Logger_1793::write_log_file(LogInfoMsg, "Программа аварийно завершена\n");
    std::exit(-1);
}
