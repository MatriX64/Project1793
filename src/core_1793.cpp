#include "include/core_1793.h"

Core_1793::Core_1793(int argc, char *argv[])
{
    application = new QGuiApplication(argc, argv);
    model = new Model_1793;
    module_manager = new ModuleManager_1793;

    connect(module_manager, SIGNAL(send_log_file(int,const QString&)), this, SLOT(write_log_file(int,const QString&)));
    connect(model, SIGNAL(send_log_file(int,const QString&)), this, SLOT(write_log_file(int,const QString&)));
    connect(module_manager, SIGNAL(quit_critical_sender()), this, SLOT(quit_critical_receiver()));
    connect(model, SIGNAL(quit_critical_sender()), this, SLOT(quit_critical_receiver()));
    connect(model, SIGNAL(quit_normal_sender()), this, SLOT(quit_normal_receiver()));

    open_log_file();

    model->start();
    module_manager->start();

    main_view = new (QQmlApplicationEngine);
    main_view->load(QUrl(QStringLiteral("/home/san/Qt/Projects/Project1793/qml/main_view.qml")));
}

Core_1793::~Core_1793()
{
    delete (module_manager);
    delete (model);
    delete (main_view);

    write_log_file(LogInfoMsg, "Программа завершена\n");
    m_logFile->close();
    delete (m_logFile);
    delete (application);
}

void Core_1793::open_log_file()
{
    m_logFile = new QFile(module_manager->app_dir.absolutePath() + "/log");
    m_logFile->open(QIODevice::WriteOnly);

    write_log_file(LogInfoMsg, "Программа запущена");
}

void Core_1793::write_log_file(int type, const QString& msg)
{
    QTextStream out(m_logFile);
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    switch (type)
    {
    case LogInfoMsg:     out << "INF "; break;
    case LogDebugMsg:    out << "DBG "; break;
    case LogWarningMsg:  out << "WRN "; break;
    case LogCriticalMsg: out << "CRT "; break;
    case LogFatalMsg:    out << "FTL "; break;
    }
    out << ": " << msg << endl;
    out.flush();
}

void Core_1793::quit_critical_receiver()
{
    QQmlApplicationEngine fatal_message;
    fatal_message.load("/home/san/Qt/Projects/Project1793/qml/fatal_message.qml");

    QObject::connect(application, SIGNAL(lastWindowClosed()), this, SLOT(quit_critical()));

    QObject *item = fatal_message.rootObjects().first();
    QObject::connect(item, SIGNAL(quit_signal()), this, SLOT(quit_critical()));

    application->exec();
}

void Core_1793::quit_critical()
{   
    write_log_file(LogInfoMsg, "Программа аварийно завершена\n");
    m_logFile->close();
    delete (m_logFile);
    delete (application);
    std::exit(-1);
}

void Core_1793::quit_normal_receiver()
{
    application->quit();
}
