#pragma once

#include <gf/gf_task.h>
#include <mt/mt_vector.h>
#include <types.h>

class MuObject;
namespace nw4r { namespace g3d { class ScnObj; } }

// Final Smash HP-window task, identified by its RTTI and status-process callers.
class IfMarthFinalTask : public gfTask {
public:
    u8 unk40[8];
    nw4r::g3d::ScnObj* unk48;
    MuObject* m_objects[1];
    nw4r::g3d::ScnObj* m_sceneObjects[1];
    u8 unk54[0x24];
    Vec3f m_positionConv;
    u8 unk84;
    u8 unk85[3];
    u8 unk88;
    u8 unk89[3];

    void initWork();
    void destroyModel();
    void setPosConv(const Vec3f* position);
    void dispOn(int);
    void dispOff(int);
    void setVisibilityWhole(bool visible);
    void setPos(Vec3f* position, int index);
    Vec3f getGlobalPos(int index);
    u32 isExecutedCallBack() const;
};
static_assert(sizeof(IfMarthFinalTask) == 0x8c, "Class is wrong size!");
