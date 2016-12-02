#ifndef WPS_ATTACK_MODULE_H
#define WPS_ATTACK_MODULE_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QStringList>
#include <QQmlComponent>
#include <QPointer>
#include <QProcess>
#include <QRegularExpression>

#include "../core/module_1793.h"

class WPS_Attack_module : public QObject
{
    Q_OBJECT
public:
    explicit WPS_Attack_module(QObject* parent = 0);
    ~WPS_Attack_module();

    int number = 1;

private:
    QString monitorInterface;

    QPointer<QProcess> loadWPSLits;

    void append_new_message_to_std(const QVariant &data);
    QString switch_interface_to_monitor(const QString& interface);
    void switch_interface_to_station();

public slots:
    void startup_initialization();

    void refresh_interfaces_list();

    void refresh_WPS_networks_list(const QString& interface);
    void stop_refreshing_WPS_list();
    void handle_refreshing_WPS_data();

signals:
    void clear_interfaces_list_model();
    void clear_WPS_list_model();
    void add_new_WPS_network(const Network &network);
    void add_new_interface(const QString &interface);
};

#endif // WPS_ATTACK_MODULE_H
