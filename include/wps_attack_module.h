#ifndef WPS_ATTACK_MODULE_H
#define WPS_ATTACK_MODULE_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QStringList>
#include <QQmlComponent>

#include "module_1793.h"

class WPS_Attack_module : public QObject
{
    Q_OBJECT
public:
    explicit WPS_Attack_module(QObject* parent = 0);
    ~WPS_Attack_module();

    int number = 1;

public slots:
    void refresh_WPS_networks_list();

signals:
    void clear_interfaces_list_model();
    void clear_WPS_list_model();
    void add_new_WPS_network(const Network &network);
};

#endif // WPS_ATTACK_MODULE_H
