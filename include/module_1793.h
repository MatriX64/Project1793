#ifndef MODULE_1793_H
#define MODULE_1793_H

#include <QString>
#include <QFile>
#include <QRegularExpression>
#include <QDebug>

class Module_1793
{
public:
    explicit Module_1793(const QString& module_name);
    ~Module_1793();

public:
    void add_module_to_layout(const QString& module_name);
};

#endif // MODULE_1793_H
