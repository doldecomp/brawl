#pragma once

#include <gf/gf_task.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <so/status/so_status_module_impl.h>
#include <types.h>

class soModuleAccesser;
class MuObject;

class ftPeachStatusUniqProcessFinal : public soStatusUniqProcess {
public:
    virtual ~ftPeachStatusUniqProcessFinal() {}
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int nextStatus);

    void setOutAction(soModuleAccesser* moduleAccesser);
    bool createInfo(soModuleAccesser* moduleAccesser);
    void destroyInfo(soModuleAccesser* moduleAccesser);
};

// Native status code uses one companion task for its screen-space blossom model.
// Field names below follow the offsets written by the constructor and update code.
class IfPeachFinalTask : public gfTask {
public:
    nw4r::g3d::ResFile m_resource;  // +0x40
    s32 unk44;                      // +0x44
    void* m_group;                  // +0x48: native stores the created scene group here
    MuObject* m_model;              // +0x4C
    s32 m_soundHandle;              // +0x50
    u32 m_fighterTaskId;             // +0x54
    bool m_actionActive;             // +0x58
    bool m_registered;               // +0x59
    u8 unk5a[2];

    IfPeachFinalTask(void* resourceData, u32 fighterTaskId);
    virtual ~IfPeachFinalTask();
    virtual void processFixPosition();

    static IfPeachFinalTask* create(void* resourceData, s32 heap, u32 fighterTaskId, bool initialize);
    void initProc(nw4r::g3d::ResFile* resource, void* group, s32 heap, bool priorityOffset);
    void initWork();
    void createModel(nw4r::g3d::ResFile* resource, s32 heap, bool priorityOffset);
    void destroyModel();
    void setAction(int action);
    void setRate(float rate);
    void setVisibilityWhole(bool visible);
};
static_assert(sizeof(IfPeachFinalTask) == 0x5C, "IfPeachFinalTask size mismatch");

extern ftPeachStatusUniqProcessFinal g_ftPeachStatusUniqProcessFinal;
