#ifndef MODULE_1793_H
#define MODULE_1793_H

#include <QString>
#include <QRegularExpression>
#include <QDebug>

#include "datacommunicator.h"

class Module_1793 : public DataCommunicator
{
    Q_OBJECT
public:
    explicit Module_1793();
    ~Module_1793();

    Model_1793 *mainModel;

public:
    void add_module_to_layout(const QString& moduleName, const QString &fileName);
};

#endif // MODULE_1793_H
