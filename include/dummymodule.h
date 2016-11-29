#ifndef DUMMYMODULE_H
#define DUMMYMODULE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QStringList>
#include <QQmlComponent>
#include <QThread>
#include <QDebug>

#include "module_1793.h"

class DummyModule : public QObject
{
    Q_OBJECT
public:
    DummyModule(QObject *parent = 0);

public slots:
    void qmlSignalHandler();
};

#endif // DUMMYMODULE_H
