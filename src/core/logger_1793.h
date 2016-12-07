#ifndef LOGGER_1793_H
#define LOGGER_1793_H

#define LogInfoMsg     0
#define LogDebugMsg    1
#define LogWarningMsg  2
#define LogCriticalMsg 3
#define LogFatalMsg    4

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QCoreApplication>
#include <QDebug>

class Logger_1793 : public QObject
{
    Q_OBJECT
public:
    Logger_1793(QObject* parent = 0);
    ~Logger_1793();

public:
    static QFile mLogFile;

    static void write_log_file(int type, const QString& msg);
    void initialize();
};

#endif // LOGGER_1793_H
