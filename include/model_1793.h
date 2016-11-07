#ifndef MODEL_1793_H
#define MODEL_1793_H

#include <QQmlApplicationEngine>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QVariant>

#include "name_codes_1793.h"

#include <QDebug>

typedef QMap<QString,QString> TabViewModel;

class Model_1793 : public QObject
{
    Q_OBJECT
public:
    Model_1793();
    Model_1793(Model_1793*);
    ~Model_1793();

public:
    QStringList networkList;
    TabViewModel qmlTabView;
    QString str;

public:
    void start();

signals:
    void send_log_file(int, const QString&);
    void quit_critical_sender();
    void quit_normal_sender();

};

#endif // MODEL_1793_H
