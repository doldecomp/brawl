#pragma once

#include <StaticAssert.h>
#include <gf/gf_scene.h>
#include <types.h>

class scStaffRoll : public gfScene {
public:
    static scStaffRoll* create();
    scStaffRoll(const char* name) : gfScene(name) { }
    virtual void start();
    virtual s32 process();
    virtual s32 exit();
};
static_assert(sizeof(scStaffRoll) == 0x8, "Class is the wrong size!");
