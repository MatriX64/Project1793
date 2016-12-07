#ifndef MODEL_1793_H
#define MODEL_1793_H

#include <QQmlApplicationEngine>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QQmlContext>
#include <QSharedPointer>
#include <QVariant>
#include <QThread>

#include "../logger_1793.h"
#include "wpsnetworklistmodel.h"
#include "interfacesmodel.h"

#include <QDebug>

class Model_1793 : public QObject
{
    Q_OBJECT
public:
    Model_1793(QQmlApplicationEngine *engine, QObject* parent = 0);
    ~Model_1793();
    static Model_1793* model;

private: //modules data
    WPSNetworkListModel networksList;
    InterfacesModel interfacesList;


public:
    void start();

public slots: //modules data slots
    void add_new_network(const Network &network);
    void clear_WPS_networks_list();
    void add_new_interface(const QString &interface);
    void clear_interfaces_list();

public: //sysyem data
    static QMap<QString,QString> qmlTabView;
    static QList<QString> modulesList;
};

#endif // MODEL_1793_H
