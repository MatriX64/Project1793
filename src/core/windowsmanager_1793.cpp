#include "src/core/windowsmanager_1793.h"

#include <QDebug>
#include <QQmlContext>

QQmlApplicationEngine* WindowsManager_1793::mainViewEngine;
bool WindowsManager_1793::isWindowsManagerInitialized = false;
bool WindowsManager_1793::isMainViewLoaded = false;

bool WindowsManager_1793::isInformationLoaded = false;
bool WindowsManager_1793::isWarningLoaded = false;
bool WindowsManager_1793::isErrorLoaded = false;

bool WindowsManager_1793::isNotificationInvoked = false;

WindowsManager_1793::WindowsManager_1793()
{

}

void WindowsManager_1793::initialize(QQmlApplicationEngine &engine)
{
    if (isWindowsManagerInitialized == true)
    {
        qWarning("QQmlApplicationEngine already initialized");
        return;
    } else
    {
        mainViewEngine = &engine;
        isWindowsManagerInitialized = true;
    }
}

void WindowsManager_1793::load_main_view(const QUrl &mainViewFilePath)
{
    if (isWindowsManagerInitialized == false)
    {
        qWarning("WindowsManager is not initialized");
        return;
    } else
    if (isMainViewLoaded == true)
    {
        qWarning("QQmlApplicationEngine already loaded");
        return;
    } else
    {
        mainViewEngine->load(mainViewFilePath);
        WindowsManager_1793::isMainViewLoaded = true;
    }
}

void WindowsManager_1793::load_main_view(const QByteArray &mainViewData)
{
    if (isWindowsManagerInitialized == false)
    {
        qWarning("WindowsManager is not initialized");
        return;
    } else
    if (isMainViewLoaded == true)
    {
        qWarning("QQmlApplicationEngine already loaded");
        return;
    } else
    {
        mainViewEngine->loadData(mainViewData);
        WindowsManager_1793::isMainViewLoaded = true;
    }
}

QObject *WindowsManager_1793::getQmlRootObject()
{
    if (isMainViewLoaded == false)
    {
        qWarning("Cannot get qmlRootObject. WindowsManager is not initialized");
        return nullptr;
    } else
    {
        QObject* rootObject = mainViewEngine->rootObjects().first();
        return rootObject;
    }
}

QList<QObject*> WindowsManager_1793::getQmlRootObjects()
{
    if (isMainViewLoaded == false)
    {
        qWarning("Cannot get qmlRootObjects. WindowsManager is not initialized");
        return QList<QObject*>();
    } else
    {
        QList<QObject*> rootObjects = mainViewEngine->rootObjects();
        return rootObjects;
    }
}

QObject *WindowsManager_1793::getQmlObject(const QString &objectName)
{
    if (isMainViewLoaded == false)
    {
        qWarning("Cannot get qmlObject. WindowsManager is not initialized");
        return nullptr;
    } else
    {
        QObject* object = mainViewEngine->rootObjects().first()->findChild<QObject*>(objectName);
        return object;
    }
}

void WindowsManager_1793::setContextProperty(const QString &propertyName, const QVariant &property)
{
    if (isMainViewLoaded == true)
    {
        qWarning("Cannot set property. QQmlApplicationEngine already initialized");
        return;
    } else
    {
        mainViewEngine->rootContext()->setContextProperty(propertyName, property);
    }
}

void WindowsManager_1793::show_notification_info(const QString& message)
{
    if (isWindowsManagerInitialized == false)
    {
        qWarning("WindowsManager is not initialized");
        return;
    } else
    {
        if (isNotificationInvoked == true)
        {
            qWarning("Cannot show multiple notification windows at same time");
            return;
        } else if (isInformationLoaded == false)
        {
            mainViewEngine->load(QUrl("qrc:/src/core/interfaces/InfoMessage.qml"));
            isInformationLoaded = true;
        }
        isNotificationInvoked = true;

        QObject* moduleObject;
        for (int i = 0; i < mainViewEngine->rootObjects().count(); i++)
        {
            QString objectName = mainViewEngine->rootObjects().at(i)->objectName();
            if (!objectName.compare("information"))
            {
                moduleObject = mainViewEngine->rootObjects().at(i);
                break;
            }
        }
        moduleObject->setProperty("text", message);
        moduleObject->setProperty("visible", "true");

        QEventLoop localLoop;
        QObject::connect(moduleObject, SIGNAL(closeSignal()), &localLoop, SLOT(quit()));
        localLoop.exec(QEventLoop::DialogExec);

        isNotificationInvoked = false;
    }
}

void WindowsManager_1793::show_notification_warning(const QString& message)
{
    if (isWindowsManagerInitialized == false)
    {
        qWarning("WindowsManager is not initialized");
        return;
    } else
    {
        if (isNotificationInvoked == true)
        {
            qWarning("Cannot show multiple notification windows at same time");
            return;
        } else if (isWarningLoaded == false)
        {
            mainViewEngine->load(QUrl("qrc:/src/core/interfaces/WarningMessage.qml"));
            isWarningLoaded = true;
        }
        isNotificationInvoked = true;

        QObject* moduleObject;
        for (int i = 0; i < mainViewEngine->rootObjects().count(); i++)
        {
            QString objectName = mainViewEngine->rootObjects().at(i)->objectName();
            if (!objectName.compare("warning"))
            {
                moduleObject = mainViewEngine->rootObjects().at(i);
                break;
            }
        }
        moduleObject->setProperty("text", message);
        moduleObject->setProperty("visible", "true");

        QEventLoop localLoop;
        QObject::connect(moduleObject, SIGNAL(accepted()), &localLoop, SLOT(quit()));
        localLoop.exec(QEventLoop::ExcludeSocketNotifiers | QEventLoop::X11ExcludeTimers);
        qDebug() << "here";
        isNotificationInvoked = false;
    }
}

void WindowsManager_1793::show_notification_critical(const QString& message)
{
    if (isWindowsManagerInitialized == false)
    {
        qWarning("WindowsManager is not initialized");
        return;
    } else
    {
        if (isNotificationInvoked == true)
        {
            qWarning("Cannot show multiple notification windows at same time");
            return;
        } else if (isErrorLoaded == false)
        {
            mainViewEngine->load(QUrl("qrc:/src/core/interfaces/FatalMessage.qml"));
            isErrorLoaded = true;
        }
        isNotificationInvoked = true;

        QObject* moduleObject;
        for (int i = 0; i < mainViewEngine->rootObjects().count(); i++)
        {
            QString objectName = mainViewEngine->rootObjects().at(i)->objectName();
            if (!objectName.compare("error"))
            {
                moduleObject = mainViewEngine->rootObjects().at(i);
                break;
            }
        }
        moduleObject->setProperty("text", message);
        moduleObject->setProperty("visible", "true");

        QEventLoop localLoop;
        QObject::connect(moduleObject, SIGNAL(closeSignal()), &localLoop, SLOT(quit()));
        localLoop.exec(QEventLoop::DialogExec);

        isNotificationInvoked = false;
    }
}
