#ifndef ROGUEAP_ATTACK_MODULE_H
#define ROGUEAP_ATTACK_MODULE_H

#include "../core/module_1793.h"

class RogueAP_Attack_module : public Module_1793
{
    Q_OBJECT
public:
    RogueAP_Attack_module();

public slots:
    void start_module();
    void terminate_module();
};

#endif // ROGUEAP_ATTACK_MODULE_H
