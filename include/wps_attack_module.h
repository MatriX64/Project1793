#ifndef WPS_ATTACK_MODULE_H
#define WPS_ATTACK_MODULE_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include "module_1793.h"

class WPS_Attack_module : public QObject
{
    Q_OBJECT
public:
    explicit WPS_Attack_module(QObject* parent = 0);
    ~WPS_Attack_module();

public slots:
    void qmlSignalHandler();
};

#endif // WPS_ATTACK_MODULE_H
