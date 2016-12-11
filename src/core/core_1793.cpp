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

#include "core_1793.h"

Core_1793::Core_1793(QObject *parent) :
    QObject(parent),
    mainView(new QQmlApplicationEngine),
    model(new Model_1793(mainView)),
    initializer(new Initializer_1793)
{

}

Core_1793::~Core_1793()
{
    if (initializer->initializer_status == true)
        delete (moduleManager);
    delete (initializer);
    delete (model);
    delete (mainView);

    Logger_1793::write_log_file(LogInfoMsg, "Program terminated");
}

void Core_1793::start()
{
    //qDebug() << "Current thread:" << QThread::currentThread();
    Logger_1793::write_log_file(LogInfoMsg, "Program started");
    model->start();

    QQmlEngine splashEngine;
    QQmlComponent splashComponent(&splashEngine, QUrl("qrc:/src/core/interfaces/LauncherView.qml"));
    QObject* splashObject = splashComponent.create();
    QQuickWindow* splashWindow = qobject_cast<QQuickWindow*>(splashObject);
    splashWindow->show();

    QThread launcherThread;
    QEventLoop launchViewLoop;
    initializer->moveToThread(&launcherThread);
    connect(&launcherThread, SIGNAL(started()),               initializer,     SLOT(initialize()));
    connect(initializer,     SIGNAL(finish_initialization()), &launcherThread, SLOT(quit()));
    connect(initializer,     SIGNAL(finish_initialization()), &launcherThread, SLOT(deleteLater()));
    connect(initializer,     SIGNAL(finish_initialization()), &launchViewLoop, SLOT(quit()));
    launcherThread.start();
    launchViewLoop.exec();

    if (initializer->initializer_status == false)
    {
        mainView->load(QUrl("qrc:/src/core/interfaces/FatalMessage.qml"));
        QObject *receiver = mainView->rootObjects().first();
        connect(receiver, SIGNAL(quit_signal()), this, SLOT(terminate_crirical()));
    } else
    {
        mainView->load(QCoreApplication::applicationDirPath() + "/src/modules/interfaces/main_view.qml");
        moduleManager = new ModuleManager_1793(this);
        moduleManager->start();
    }
    splashWindow->close();
    delete (splashObject);
}

void Core_1793::terminate_crirical()
{
    qDebug() << "Terminated critical";
    QCoreApplication::exit(EXIT_FAILURE);
}
