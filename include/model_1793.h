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
    Model_1793(QObject* parent = 0);
    ~Model_1793();

public:
    static QStringList networkList;
    static QMap<QString,QString> qmlTabView;

public:
    void start();

signals:
};

#endif // MODEL_1793_H
