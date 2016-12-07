#ifndef MODULE_1793_H
#define MODULE_1793_H

#include <QString>
#include <QGuiApplication>
#include <QRegularExpression>
#include <QDebug>
#include <QObject>
#include <QPointer>
#include <QThread>

#include "app_data/model_1793.h"

class Module_1793 : public QObject
{
    Q_OBJECT
public:
    explicit Module_1793(QQmlApplicationEngine *engine, QObject *parent = 0);
    ~Module_1793();

public:
    static QObject* qmlRootObjectHandler;
    void add_module(QObject *moduleObject);

public slots:
    void start_modules();
    void terminate_modules();

signals:
    void terminate_module_signal();

private:
    QList<QObject*>* modulesList = new QList<QObject*>;
    QList<QThread*>* threadList  = new QList<QThread*>;
    QObject *moduleObjectHandler;
};

#endif // MODULE_1793_H
