#include "include/core_1793.h"

Core_1793::Core_1793(QObject *parent) : QObject(parent)
{

}

Core_1793::~Core_1793()
{
    delete (initializer);
    delete (moduleManager);
    delete (model);
    delete (mainView);

    Logger_1793::write_log_file(LogInfoMsg, "Программа завершена");

    delete (logger);
}

void Core_1793::start()
{
    //qDebug() << "Current thread:" << QThread::currentThread();
    logger = new Logger_1793(this);
    mainView = new QQmlApplicationEngine(this);
    model = new Model_1793(mainView, this);
    splashView = new QQmlApplicationEngine(this);
    initializer = new Initializer_1793;

    logger->initialize();
    model->start();

    splashView->load(QUrl("qrc:/qml/LauncherView.qml"));

    QEventLoop launchViewLoop;
    QThread *launchThread = new QThread;
    initializer->moveToThread(launchThread);
    connect(launchThread, SIGNAL(started()),               initializer,     SLOT(initialize()));
    connect(initializer,  SIGNAL(finish_initialization()), launchThread,    SLOT(quit()));
    connect(initializer,  SIGNAL(finish_initialization()), launchThread,    SLOT(deleteLater()));
    connect(initializer,  SIGNAL(finish_initialization()), &launchViewLoop, SLOT(quit()));
    connect(initializer,  SIGNAL(finish_initialization()), splashView,      SLOT(deleteLater()));
    connect(initializer,  SIGNAL(critical_error()),        launchThread,    SLOT(quit()));
    connect(initializer,  SIGNAL(critical_error()),        launchThread,    SLOT(deleteLater()));
    connect(initializer,  SIGNAL(critical_error()),        this,            SLOT(terminate_critical()));
    launchThread->start();
    launchViewLoop.exec();

    mainView->load(QCoreApplication::applicationDirPath() + "/qml/main_view.qml");

    moduleManager = new ModuleManager_1793(mainView, this);
    moduleManager->start();
}

void Core_1793::terminate_critical()
{
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
