#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <types.h>

class stShadow : public gfTask {
    char _0x40[0x24c];
public:
    virtual void renderPre();
    virtual ~stShadow();

    void clearShadowObject();
};
