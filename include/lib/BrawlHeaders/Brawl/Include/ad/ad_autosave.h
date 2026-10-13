#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <types.h>

class adAutoSave : public gfTask {
    u8 unk0[0x10];
public:
    virtual void processDefault();
    virtual void init();
    virtual ~adAutoSave();

    static adAutoSave* create(bool p1);
    static bool isAlive();
};
static_assert(sizeof(adAutoSave) == 0x50, "Class is the wrong size!");
