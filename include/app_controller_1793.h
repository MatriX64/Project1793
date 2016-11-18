#ifndef TERMINATOR_1793_H
#define TERMINATOR_1793_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>

#include "logger_1793.h"

class AppController_1793 : public QObject
{
    Q_OBJECT
public:
    explicit AppController_1793(QObject *parent = 0);
    ~AppController_1793();

    static QGuiApplication *application;

    static void terminate_normal();
    static void terminate_critical();
signals:

public slots:
};

#endif // TERMINATOR_1793_H
