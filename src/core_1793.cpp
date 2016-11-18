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

    splashView->load(QUrl(QStringLiteral("/home/san/Qt/Projects/Project1793/qml/LauncherView.qml")));

    QEventLoop launchViewLoop;
    QThread *launchThread = new QThread;
    moduleManager->moveToThread(launchThread);
    connect(moduleManager, SIGNAL(finishLaunchRoutine()), &launchViewLoop, SLOT(quit()));
    connect(launchThread, SIGNAL(started()), moduleManager, SLOT(startLaunchRoutine()));
    connect(moduleManager, SIGNAL(finishLaunchRoutine()), launchThread, SLOT(quit()));
    connect(moduleManager, SIGNAL(finishLaunchRoutine()), launchThread, SLOT(deleteLater()));
    connect(moduleManager, SIGNAL(finishLaunchRoutine()), &launchViewLoop, SLOT(quit()));
    connect(moduleManager, SIGNAL(finishLaunchRoutine()), splashView, SLOT(deleteLater()));
    launchThread->start();
    launchViewLoop.exec();
    QThread::sleep(3);

    qDebug() << moduleManager->test;

    mainView->load(QUrl(QStringLiteral("/home/san/Qt/Projects/Project1793/qml/main_view.qml")));
}
