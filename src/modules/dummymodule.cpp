#include "dummymodule.h"

DummyModule::DummyModule(QObject *parent) : QObject(parent)
{
    connect(Module_1793::qmlRootObjectHandler, SIGNAL(signalDummy()), this, SLOT(qmlSignalHandler()));
}

void DummyModule::initialize()
{

}

void DummyModule::terminate()
{
    qDebug() << "Dummy termination";
}

void DummyModule::qmlSignalHandler()
{
    qDebug() << "Current thread:" << QThread::currentThread();
}
