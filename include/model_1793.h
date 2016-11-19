#ifndef MODEL_1793_H
#define MODEL_1793_H

#include <QQmlApplicationEngine>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QVariant>

#include "logger_1793.h"
#include "name_codes_1793.h"

#include <QDebug>

class Model_1793 : public QObject
{
    Q_OBJECT
public:
    Model_1793();
    Model_1793(Model_1793*);
    ~Model_1793();

public:
    QStringList networkList;
    QMap<QString,QString> qmlTabView;
    QString str;

public:
    void start();

signals:
};

#endif // MODEL_1793_H
