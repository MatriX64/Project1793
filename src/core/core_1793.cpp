#include "core_1793.h"

Core_1793::Core_1793(QGuiApplication *application, QObject *parent) :  QObject(parent),
                                                                       appHandler(application)

{

}

Core_1793::~Core_1793()
{
    if (initializer->initializer_status == true)
    {        
        delete (moduleManager);
    }
    delete (mainView);
    delete (initializer);
    delete (model);

    Logger_1793::write_log_file(LogInfoMsg, "Программа завершена");

    delete (logger);
}

void Core_1793::start()
{
    //qDebug() << "Current thread:" << QThread::currentThread();
    logger = new Logger_1793(this);
    mainView = new QQmlApplicationEngine(this);
    model = new Model_1793(mainView, this);
    initializer = new Initializer_1793;

    logger->initialize();
    model->start();

    QQmlEngine splashEngine;
    QQmlComponent splashComponent(&splashEngine, QUrl("qrc:/src/core/interfaces/LauncherView.qml"));
    QPointer<QObject> splashObject = splashComponent.create();
    QPointer<QQuickWindow> splashWindow = qobject_cast<QQuickWindow*>(splashObject);
    splashWindow->show();

    QEventLoop launchViewLoop;
    launchThread = new QThread;
    initializer->moveToThread(launchThread);
    connect(launchThread, SIGNAL(started()),               initializer,     SLOT(initialize()));
    connect(initializer,  SIGNAL(finish_initialization()), launchThread,    SLOT(quit()));
    connect(initializer,  SIGNAL(finish_initialization()), launchThread,    SLOT(deleteLater()));
    connect(initializer,  SIGNAL(finish_initialization()), &launchViewLoop, SLOT(quit()));
    launchThread->start();
    launchViewLoop.exec();

    if (initializer->initializer_status == false)
    {
        mainView->load(QUrl("qrc:/src/core/interfaces/fatal_message.qml"));
        QObject *receiver = mainView->rootObjects().first();
        connect(receiver, SIGNAL(quit_signal()), this, SLOT(terminate_crirical()));
    } else
    {
        mainView->load(QCoreApplication::applicationDirPath() + "/src/modules/interfaces/main_view.qml");
        moduleManager = new ModuleManager_1793(mainView, this);
        connect(appHandler, SIGNAL(aboutToQuit()), &moduleManager->moduleController, SLOT(terminate_modules()));
        moduleManager->start();
    }
    splashWindow->close();
}

void Core_1793::terminate_crirical()
{
    Logger_1793::write_log_file(LogInfoMsg, "Программа аварийно завершена\n");
    qDebug() << "Terminated critical";
    appHandler->exit(EXIT_FAILURE);
}
