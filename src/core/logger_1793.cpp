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

#include "logger_1793.h"

Logger_1793::Logger_1793(QObject *parent) : QObject(parent)
{

}

Logger_1793::~Logger_1793()
{

}

void Logger_1793::write_log_file(int type, const QString &msg)
{
    QFile mLogFile;
    mLogFile.setFileName(QCoreApplication::applicationDirPath() + "/log");
    mLogFile.open(QIODevice::WriteOnly | QIODevice::Append);

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

    mLogFile.close();
}
