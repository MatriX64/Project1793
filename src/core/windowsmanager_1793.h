/*
 * Copyright (c) 2016,2017 sanmira32 <matrix3sai@gmail.com>
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

#ifndef WINDOWSMANAGER_1793_H
#define WINDOWSMANAGER_1793_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QEventLoop>
#include <QObject>
#include <QUrl>

class WindowsManager_1793
{
public:
    WindowsManager_1793();

public:
    void load_main_view(const QUrl& mainViewFilePath);
    void load_main_view(const QByteArray& mainViewData);

    static void initialize(QQmlApplicationEngine& engine);
    static QObject* getQmlRootObject();
    static QList<QObject*> getQmlRootObjects();
    static QObject* getQmlObject(const QString &objectName);
    static void setContextProperty(const QString& propertyName, const QVariant& property);

    static void show_notification_info(const QString &message);
    static void show_notification_warning(const QString& message);
    static void show_notification_critical(const QString &message);

private:
    static QQmlApplicationEngine* mainViewEngine;
    static bool isWindowsManagerInitialized;
    static bool isMainViewLoaded;

    static bool isInformationLoaded;
    static bool isWarningLoaded;
    static bool isErrorLoaded;

    static bool isNotificationInvoked;
};

#endif // WINDOWSMANAGER_1793_H
