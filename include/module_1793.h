#ifndef MODULE_1793_H
#define MODULE_1793_H

#include <QString>
#include <QRegularExpression>
#include <QDebug>
#include <QObject>
#include <QPointer>
#include <QThread>

#include "model_1793.h"

class Module_1793 : public QObject
{
    Q_OBJECT
public:
    explicit Module_1793(QQmlApplicationEngine *engine, QObject *parent = 0);
    ~Module_1793();

public:
    static QObject* qmlSignals;
    void add_module(QObject *moduleObject);

public slots:
    void start_modules();

private:
    QList<QObject*>* modulesList = new QList<QObject*>;
    QObject *moduleObjectHandler;
};

#endif // MODULE_1793_H
