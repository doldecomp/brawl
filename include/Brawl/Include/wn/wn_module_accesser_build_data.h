#pragma once

#include <StaticAssert.h>
#include <so/ground/so_ground_module_impl.h>
#include <so/so_common_data_accesser.h>
#include <so/so_module_accesser_build_data.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <sr/sr_common.h>
#include <types.h>

class wnModuleAccesserBuildData : public soModuleAccesserBuildData {
public:
    // TODO: add missing params
    wnModuleAccesserBuildData(s32 entryId, s32 kind, Heaps::HeapType instHeap,
                       Heaps::HeapType nwModelInstHeap,
                       Heaps::HeapType nwMotionInstHeap,
                       s8 resGroupNo, soModuleAccesser* acc,
                       s32 team, void* cameraRangeSet,
                       void* cameraClipSphereSet);

    virtual u32 getMdlResId() const;
    virtual u32 getAnmResId() const;
    virtual u8 getResGroupNo() const;
    virtual s32 getTeam() const;
    virtual wnMotionData* getMotionData() const;
    virtual wnShakeData* getShakeData() const;
    virtual wnVisibilityData* getVisibilityData() const;
    virtual wnStatusData* getStatusData() const;
    virtual soGroundConditionChecker* getGroundConditionChecker() const;
    virtual void* getEffectEmitData() const;
    virtual wnEffectCommonData* getEffectCommonData() const;
    virtual soParamAccesser* getParamAccesser() const;
    virtual s32 getAreaCategory() const;
    virtual void* getCameraRangeSet() const;
    virtual void* getCameraClipSphereSet() const;
    virtual void* getItemNodeData() const;
    virtual wnJostleData* getJostleData() const;
    virtual Heaps::HeapType getInstanceHeap() const;
    virtual Heaps::HeapType getNWMotionInstanceHeap() const;
    virtual Heaps::HeapType getNWModelInstanceHeap() const;
    virtual ~wnModuleAccesserBuildData();
    virtual void* getAnimCmdData(u32 eventThread, s32 p2) const;
};
// TODO: size
