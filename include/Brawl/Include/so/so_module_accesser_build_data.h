#pragma once

#include <StaticAssert.h>
#include <so/ground/so_ground_module_impl.h>
#include <so/so_common_data_accesser.h>
#include <so/so_value_accesser.h>
#include <sr/sr_common.h>
#include <types.h>

class soModuleAccesserBuildData {
public:
    virtual u32 getMdlResId() const = 0;
    virtual u32 getAnmResId() const = 0;
    virtual u8 getResGroupNo() const = 0;
    virtual s32 getTeam() const = 0;
    virtual soMotionData* getMotionData() const = 0;
    virtual soShakeData* getShakeData() const = 0;
    virtual soVisibilityData* getVisibilityData() const = 0;
    virtual soStatusData* getStatusData() const = 0;
    virtual soGroundConditionChecker* getGroundConditionChecker() const = 0;
    virtual void* getEffectNodeData() const { return nullptr; }
    virtual void* getEffectEmitData() const = 0;
    virtual soEffectCommonData* getEffectCommonData() const = 0;
    virtual soEffectScreenData* getEffectScreenData() const { return nullptr; };
    virtual void* getTerritoryParam() const { return nullptr; }

    // UBFIX this function has a bug; don't dereference the pointer it
    // returns! TODO flag callers of this function, if any
    virtual s32* getTerritoryRect() const {
        s32 rect[4] = { 0, 0, 0, 0 };
        return rect;
    }
    virtual void* getTargetSearchParam() const { return nullptr; }
    virtual soIkData* getIkData() const { return nullptr; }
    virtual s32 getModelLayerType() const { return 2; }
    virtual float getModelScale() const { return 1.0f; }
    virtual soParamAccesser* getParamAccesser() const = 0;
    virtual s32 getAreaCategory() const = 0;
    virtual void* getCameraRangeSet() const = 0;
    virtual void* getCameraClipSphereSet() const = 0;
    virtual void* getItemNodeData() const = 0;
    virtual void* getModelExtendNodeTable() const { return nullptr; }
    virtual soJostleData* getJostleData() const = 0;
    virtual soPreCheckAnimCmdData* getPreCheckAnimCmdData() const { return nullptr; }
    virtual Heaps::HeapType getInstanceHeap() const = 0;
    virtual Heaps::HeapType getNWModelInstanceHeap() const = 0;
    virtual Heaps::HeapType getNWMotionInstanceHeap() const = 0;
    virtual s32 getHeapSlotNo() const { return 0; }
    virtual soSoundIdExchanger* getSoundIdExchanger() const {
        return &g_soSoundIdExchangerNull;
    }
    virtual float getSlopeAngleLimit() const { return 20.0f; }
    virtual ~soModuleAccesserBuildData() { }
    virtual void* getAnimCmdData(u32 eventThread, s32 p2) const = 0;
};
static_assert(sizeof(soModuleAccesserBuildData) == 0x4, "Class is the wrong size!");
