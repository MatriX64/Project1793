#ifndef MODULE_1793_H
#define MODULE_1793_H

#include <QString>
#include <QFile>
#include <QRegularExpression>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "datacommunicator.h"

class Module_1793 : public DataCommunicator
{
    Q_OBJECT
public:
    explicit Module_1793(const QString& moduleName, const QString &file_name);
    ~Module_1793();

    Model_1793 *mainModel;

public:
    void add_module_to_layout(const QString& module_name, const QString &file_name);
};

#endif // MODULE_1793_H
