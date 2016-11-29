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

#include "logger_1793.h"
#include "name_codes_1793.h"
#include "wpsnetworklistmodel.h"

#include <QDebug>

class Model_1793 : public QObject
{
    Q_OBJECT
public:
    Model_1793(QQmlApplicationEngine *engine, QObject* parent = 0);
    ~Model_1793();
    static Model_1793* model;

private: //modules data
    WPSNetworkListModel networskList;

public:
    void start();

public slots: //modules data slots
    void add_new_network(const Network &network);

public: //sysyem data
    static QMap<QString,QString> qmlTabView;
};

#endif // MODEL_1793_H
