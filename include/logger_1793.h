#ifndef LOGGER_1793_H
#define LOGGER_1793_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QCoreApplication>
#include <QDebug>

#include "name_codes_1793.h"

class Logger_1793
{
public:
    Logger_1793();
    ~Logger_1793();

public:
    static QFile mLogFile;

    static void write_log_file(int type, const QString& msg);
    void initialize();
};

#endif // LOGGER_1793_H
