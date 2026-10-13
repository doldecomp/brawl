#pragma once

#include <StaticAssert.h>
#include <gf/gf_gameframe_counter.h>
#include <mt/mt_vector.h>
#include <so/so_module_accesser.h>
#include <types.h>

// TODO ID this class
struct UnkTargetSearchUnit {
    u8 unk0[0x14];
    float unk14;
};

// Note: inferred base class
class AbstractTargetSearchUnit {
public:
    virtual bool checkTargetExist(soModuleAccesser* acc, u32 p2) = 0;
    virtual bool checkTargetInArea(soModuleAccesser* acc, u32 p2, u32 p3) = 0;
    virtual Vec3f getTargetPos(soModuleAccesser* acc, u32 p2) = 0;
    virtual Vec3f getSelfPos(soModuleAccesser* acc) = 0;
    virtual void initInterval(soModuleAccesser* acc) = 0;
};
static_assert(sizeof(AbstractTargetSearchUnit) == 0x4, "Class is the wrong size!");

class soTargetSearchUnit : private AbstractTargetSearchUnit {
protected:
    UnkTargetSearchUnit* unk4;
    gfGameFrameCounter m_frameCounter;
    s32 unk14;
public:
    soTargetSearchUnit();
    ~soTargetSearchUnit();
    virtual bool checkTargetExist(soModuleAccesser* acc, u32 p2) = 0;
    virtual bool checkTargetInArea(soModuleAccesser* acc, u32 p2, u32 p3) = 0;
    virtual Vec3f getTargetPos(soModuleAccesser* acc, u32 p2) = 0;
    virtual Vec3f getSelfPos(soModuleAccesser* acc) = 0;
    virtual void initInterval(soModuleAccesser* acc);
};
static_assert(sizeof(soTargetSearchUnit) == 0x18, "Class is the wrong size!");
