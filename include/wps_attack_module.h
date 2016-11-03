#ifndef WPS_ATTACK_MODULE_H
#define WPS_ATTACK_MODULE_H

#include "module_1793.h"

class WPS_Attack_module : public Module_1793
{
public:
    explicit WPS_Attack_module(const QString& moduleName, const QString& fileName);
    ~WPS_Attack_module();
};

#endif // WPS_ATTACK_MODULE_H
