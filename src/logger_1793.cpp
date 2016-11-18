#include "include/logger_1793.h"

QFile Logger_1793::mLogFile("log");

Logger_1793::Logger_1793()
{

}

Logger_1793::~Logger_1793()
{
    write_log_file(LogInfoMsg, "(Logger)Logger closed");
    mLogFile.close();
}

void Logger_1793::write_log_file(int type, const QString &msg)
{
    QTextStream out(&mLogFile);
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

void Logger_1793::initialize()
{
    mLogFile.open(QIODevice::WriteOnly);

    write_log_file(LogInfoMsg, "(Logger)Logger initialized");
}
