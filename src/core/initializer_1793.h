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

#ifndef INITIALIZER_1793_H
#define INITIALIZER_1793_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QTextCodec>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>

#include "app_data/model_1793.h"
#include "logger_1793.h"

class Initializer_1793 : public QObject
{
    Q_OBJECT
public:
    explicit Initializer_1793(QObject *parent = 0);
    ~Initializer_1793();

    bool initializer_status;

public slots:
    void initialize();

private:
    bool check_packages();
    bool generate_main_view();
    void add_module_layouts();
    bool set_modules();

    static void new_module_layout(const QString &moduleName, const QString &fileName);

signals:
    void finish_initialization();

public slots:
};

#endif // INITIALIZER_1793_H
