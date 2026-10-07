#pragma once

#include <gf/gf_task.h>
#include <mt/mt_vector.h>
#include <types.h>
#include <memory.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/g3d/g3d_scnobjcallback.h>

class MuObject;
namespace nw4r { namespace g3d { class ScnObj; } }
namespace nw4r { namespace g3d { class ScnGroup; } }
namespace nw4r { namespace g3d { class ScnMdl; } }

class IfMarthFinalObjCallback : public nw4r::g3d::IScnObjCallback {
public:
    Vec3f m_position;
    u8 m_executed;
    u8 unk11[3];
    IfMarthFinalObjCallback() : m_position(0.0f, 0.0f, 0.0f), m_executed(0) {}
    virtual ~IfMarthFinalObjCallback();
    virtual void ExecCallback_CALC_WORLD(nw4r::g3d::ScnObj::Timing timing, nw4r::g3d::ScnObj* object, u32 param, void* info);
};
static_assert(sizeof(IfMarthFinalObjCallback) == 0x14, "Class is wrong size!");

// Final Smash HP-window task, identified by its RTTI and status-process callers.
class IfMarthFinalTask : public gfTask {
public:
    nw4r::g3d::ResFile m_resource;
    u32 unk44;
    nw4r::g3d::ScnObj* unk48;
    MuObject* m_objects[1];
    nw4r::g3d::ScnObj* m_sceneObjects[1];
    u8 unk54;
    u8 unk55[0x1b];
    u32 unk70;
    IfMarthFinalObjCallback m_callback;
    u8 unk88;
    u8 unk89[3];

    IfMarthFinalTask(void* resourceData);
    virtual ~IfMarthFinalTask();
    virtual void processDefault();
    static IfMarthFinalTask* create(void* resourceData, HeapType heap, int priority);
    void initWork();
    void initProc(nw4r::g3d::ResFile* resource, nw4r::g3d::ScnGroup* group, int priority, HeapType heap);
    void createModel(nw4r::g3d::ResFile* resource, int priority, HeapType heap);
    void setAnim(int index);
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
