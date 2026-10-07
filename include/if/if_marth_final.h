#pragma once

#include <gf/gf_task.h>
#include <mt/mt_vector.h>
#include <types.h>

// Final Smash HP-window task, identified by its RTTI and status-process callers.
class IfMarthFinalTask : public gfTask {
public:
    u8 unk40[8];
    void* unk48;
    u8 unk4c[0x38];
    u8 unk84;
    u8 unk85[3];
    u8 unk88;
    u8 unk89[3];

    void dispOff(int);
    void setPos(Vec3f* position, int index);
    Vec3f getGlobalPos(int index);
    u32 isExecutedCallBack() const;
};
static_assert(sizeof(IfMarthFinalTask) == 0x8c, "Class is wrong size!");
