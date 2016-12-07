#include "module_1793.h"

QObject*               Module_1793::qmlRootObjectHandler;

Module_1793::Module_1793(QQmlApplicationEngine *engine, QObject *parent) : QObject(parent)
{
    qmlRootObjectHandler = engine->rootObjects().first();
}

Module_1793::~Module_1793()
{
    delete (modulesList);
    delete (threadList);
}

void Module_1793::add_module(QObject *moduleObject)
{
    modulesList->append(moduleObject);
    threadList->append(new QThread(this));
}

void Module_1793::start_modules()
{
    for (int i = 0; i < modulesList->count(); i++)
    {
        modulesList->at(i)->moveToThread(threadList->at(i));
        connect(threadList->at(i), SIGNAL(started()), modulesList->at(i), SLOT(initialize()));
        threadList->at(i)->start();
    }
}

void Module_1793::terminate_modules()
{
    for (int i = 0; i < modulesList->count(); i++)
    {
        connect(this, SIGNAL(terminate_module_signal()), modulesList->at(i), SLOT(terminate()));
        emit terminate_module_signal();
        threadList->at(i)->quit();
        threadList->at(i)->wait(-1);
        delete (threadList->at(i));
    }
}
