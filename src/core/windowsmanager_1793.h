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
