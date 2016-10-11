#include "include/core_1793.h"

Core_1793::Core_1793(int argc, char *argv[])
{
    application = new QGuiApplication(argc, argv);
    module_manager = new ModuleManager_1793;
    model = new Model_1793;
    QObject::connect(module_manager, SIGNAL(send_log_file(int,const QString&)), this, SLOT(write_log_file(int,const QString&)));
    QObject::connect(model, SIGNAL(send_log_file(int,const QString&)), this, SLOT(write_log_file(int,const QString&)));
    QObject::connect(module_manager, SIGNAL(critical_sender()), this, SLOT(critical_receiver()));
    QObject::connect(model, SIGNAL(critical_sender()), this, SLOT(critical_receiver()));
    QObject::connect(model, SIGNAL(normal_sender()), this, SLOT(normal_receiver()));
    open_log_file();

    module_manager->start();
    model->start();
}

Core_1793::~Core_1793()
{
    quit_normal();
}

void Core_1793::open_log_file()
{
    m_logFile = new QFile(module_manager->app_dir->absolutePath() + "/log");
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

void Core_1793::critical_receiver()
{
    quit_critical();
}

void Core_1793::quit_critical()
{
    write_log_file(LogInfoMsg, "Программа аварийно завершена\n");
    m_logFile->close();
    delete (m_logFile);
    std::exit(0);
}

void Core_1793::normal_receiver()
{
    application->quit();
}

void Core_1793::quit_normal()
{
    delete (module_manager);
    delete (model);
    write_log_file(LogInfoMsg, "Программа завершена\n");
    m_logFile->close();
    delete (m_logFile);
}

