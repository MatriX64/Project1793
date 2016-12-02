#include "module_1793.h"

QObject*               Module_1793::qmlRootObjectHandler;

Module_1793::Module_1793(QQmlApplicationEngine *engine, QObject *parent) : QObject(parent)
{
    qmlRootObjectHandler = engine->rootObjects().first();
}

Module_1793::~Module_1793()
{
    delete (modulesList);
}

void Module_1793::add_module(QObject *moduleObject)
{
    modulesList->append(moduleObject);
}

void Module_1793::start_modules()
{
    for (int i = 0; i < modulesList->count(); i++)
    {
        QPointer<QThread> moduleThread = new QThread;
        modulesList->at(i)->moveToThread(moduleThread);
        connect(moduleThread, SIGNAL(started()), modulesList->at(i), SLOT(startup_initialization()));
        connect(this, SIGNAL(destroyed()), moduleThread, SLOT(quit()));
        moduleThread->start();
    }
}
