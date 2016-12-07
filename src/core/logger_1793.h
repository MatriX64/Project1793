/*
 * Copyright (c) 2016, MatriXSan <matrix3sai@gmail.com>
 *
 *  This file is part of Project1793.
 *
 *  Project1793 is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Project1793 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Project1793.  If not, see <http://www.gnu.org/licenses/>.
*/

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
