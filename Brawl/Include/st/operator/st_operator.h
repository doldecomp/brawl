#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <gm/gm_global_mode_melee.h>
#include <types.h>

class stOperator : public gfTask {
public:
    u8 m_state;
    bool m_isStart;
    bool m_isExit;
    bool m_isPause;
    gmGlobalModeMelee* m_condition;

    virtual void processBegin();
    virtual ~stOperator();
};
static_assert(sizeof(stOperator) == 72, "Class is wrong size!");