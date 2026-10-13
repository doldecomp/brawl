#pragma once

#include <StaticAssert.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_entry.h>
#include <ft/ft_sound_id_exchanger_impl.h>
#include <so/ground/so_ground_module_impl.h>
#include <so/so_common_data_accesser.h>
#include <so/so_module_accesser_build_data.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <sr/sr_common.h>
#include <types.h>

class ftFighterBuildData : public soModuleAccesserBuildData {
    s32 m_entryId;
    ftKind m_kind;
    ftData* m_ftData;
    u8 m_resGroupNo;
    s32 m_team;
    soModuleAccesser* m_moduleAccsr;
    void* m_cameraRangeSet;
    void* m_cameraClipSphereSet;
    Heaps::HeapType m_instHeap;
    Heaps::HeapType m_nwModelInstHeap;
    Heaps::HeapType m_nwMotionInstHeap;
public:
    ftFighterBuildData(s32 entryId, ftKind kind, Heaps::HeapType instHeap,
                       Heaps::HeapType nwModelInstHeap,
                       Heaps::HeapType nwMotionInstHeap,
                       u8 resGroupNo, soModuleAccesser* acc,
                       s32 team, void* cameraRangeSet,
                       void* cameraClipSphereSet);

    virtual u32 getMdlResId() const;
    virtual u32 getAnmResId() const;
    virtual u8 getResGroupNo() const;
    virtual ftMotionData* getMotionData() const;
    virtual ftShakeData* getShakeData() const;
    virtual ftVisibilityData* getVisibilityData() const;
    virtual ftStatusData* getStatusData() const;
    virtual soGroundConditionChecker* getGroundConditionChecker() const;
    virtual void* getEffectNodeData() const;
    virtual void* getEffectEmitData() const;
    virtual ftEffectCommonData* getEffectCommonData() const;
    virtual ftEffectScreenData* getEffectScreenData() const;
    virtual ftIkData* getIkData() const;
    virtual float getModelScale() const;
    virtual soParamAccesser* getParamAccesser() const;
    virtual s32 getAreaCategory() const;
    virtual void* getCameraRangeSet() const;
    virtual void* getCameraClipSphereSet() const;
    virtual void* getItemNodeData() const;
    virtual void* getModelExtendNodeTable() const;
    virtual ftJostleData* getJostleData() const;
    virtual ftPreCheckAnimCmdData* getPreCheckAnimCmdData() const;
    virtual ~ftFighterBuildData() { }
    virtual s32 getTeam() const { return m_team; }
    virtual Heaps::HeapType getInstanceHeap() const { return m_instHeap; }
    virtual Heaps::HeapType getNWModelInstanceHeap() const { return m_nwModelInstHeap; }
    virtual Heaps::HeapType getNWMotionInstanceHeap() const { return m_nwMotionInstHeap; }
    virtual s32 getHeapSlotNo() const;
    virtual ftSoundIdExchangerImpl* getSoundIdExchanger() const;
    virtual float getSlopeAngleLimit() const;
    virtual void* getAnimCmdData(u32 eventThread, s32 p2) const;

    soAnimCmdDisguiseList* getAnimCmdDisguiseList(bool p1, s32 actionType) const;
};
static_assert(sizeof(ftFighterBuildData) == 0x30, "Class is the wrong size!");
