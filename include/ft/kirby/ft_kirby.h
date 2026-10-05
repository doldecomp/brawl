#pragma once

#include <ft/ft_fighter_builder.h>
#include <so/motion/so_motion_module_impl.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Kirby-only builder variants
////////////////////////////////////////

// HYPOTHESIS: soMotionModuleImplMultiRes is a soMotionModuleImpl with 8 more bytes of state (Kirby swaps motion resources
// for the copy abilities). Opaque stand-in: constructor and destructor are not defined here.
class soMotionModuleImplMultiRes : public soMotionModuleImpl {
    u8 unk170[8];
public:
    soMotionModuleImplMultiRes(soModuleAccesser* acc, soArrayFixed<const soMotionData>* motionData, soTransitionModule* transition, soArray<soPartialAnim>* partialAnims, soArray<soOtherAnim>* otherAnims, soArray<soTransitionTermPack>* termPacks, soArray<u32>* u32s, s16 unitId, bool b, soMotionAnimObjCacheModule* animObjCache);
    virtual ~soMotionModuleImplMultiRes();
};

// Kirby has a soCollisionSearchModuleBuilder (2 parts, 1 group) after the collision catch builder, which has no member slot of
// its own in soModuleAccesserBuilder. HYPOTHESIS: it is folded into the catch builder's storage here (the module accesser
// gets the null search module either way until the slot exists).
template <typename T, u32 SearchSize>
class soCollisionCatchModuleBuildConfigWithSearch {
public:
    typedef T ModuleType;
};

template <typename T, u32 SearchSize>
class soCollisionCatchModuleBuilder<soCollisionCatchModuleBuildConfigWithSearch<T, SearchSize> > {
    soCollisionCatchModuleBuilder<soCollisionCatchModuleBuildConfig<T> > m_catchBuilder;
    u8 m_searchBuilder[SearchSize];
public:
    soCollisionCatchModuleBuilder(soModuleAccesser* acc, int taskId, gfTask::Category category, soEventObserverRegistrationDesc* regDesc) :
        m_catchBuilder(acc, taskId, category, regDesc) { }
    T* getModule() { return m_catchBuilder.getModule(); }
};

// Physics module builder with another IK handle capacity.
template <s32 IKCap, typename T>
class soPhysicsModuleBuildConfigCap {
public:
    typedef T ModuleType;
};

template <s32 IKCap, typename T>
class soPhysicsModuleBuilder<soPhysicsModuleBuildConfigCap<IKCap, T> > : public soArraySelectHolder<1, soArrayVector<soPhysicsIKHandle, IKCap>, soArrayNull<soPhysicsIKHandle> > {
    T m_physicsModule;
public:
    soPhysicsModuleBuilder(soModuleAccesser* acc, void* ikData) :
        soArraySelectHolder<1, soArrayVector<soPhysicsIKHandle, IKCap>, soArrayNull<soPhysicsIKHandle> >(IKCap, 0), m_physicsModule(acc, ikData, this->get(), 1) { }
    T* getModule() { return &m_physicsModule; }
};

// Item manage module builder with other capacities.
template <s32 CapA, s32 CapB, typename T>
class soItemManageModuleBuildConfigCaps {
public:
    typedef T ModuleType;
};

template <s32 CapA, s32 CapB, typename T>
class soItemManageModuleBuilder<soItemManageModuleBuildConfigCaps<CapA, CapB, T> > : public soArraySelectHolder<1, soArrayVector<soItemInfo, CapA>, soArrayNull<soItemInfo> > {
    soArraySelectHolder<1, soArrayVector<soItemInfo, CapB>, soArrayNull<soItemInfo> > m_items2;
    T m_itemModule;
public:
    soItemManageModuleBuilder(soModuleAccesser* acc, void* itemNodeData) :
        soArraySelectHolder<1, soArrayVector<soItemInfo, CapA>, soArrayNull<soItemInfo> >(CapA, 0), m_items2(), m_itemModule(acc, this->get(), m_items2.get(), itemNodeData, g_soItemManageNullA, g_soItemManageNullB) { }
    T* getModule() { return &m_itemModule; }
};

// Area module builder with another size (STUB: storage only, like soAreaModuleBuilder).
template <u32 Size, typename T>
class soAreaModuleBuildConfigSized {
public:
    typedef T ModuleType;
};

template <u32 Size, typename T>
class soAreaModuleBuilder<soAreaModuleBuildConfigSized<Size, T> > {
    u8 m_data[Size];
public:
    ~soAreaModuleBuilder() { m_data[1] = 1; m_data[2] = 2; m_data[3] = 3; m_data[4] = 4; m_data[5] = 5; } // STUB: non-trivial so the dtor call exists
    soAreaModuleBuilder(soModuleAccesser* acc, u8 areaCategory, soEventObserverRegistrationDesc* regDesc) { m_data[0] = 0; m_data[1] = 1; m_data[2] = 2; m_data[3] = 3; m_data[4] = 4; m_data[5] = 5; m_data[6] = 6; m_data[7] = 7; } // STUB
    void* getModule() { return m_data + 0x10; }
};

////////////////////////////////////////
// Kirby Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftKirbyInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftKirbyHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftKirbyParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftKirbyResourceIdAccesserImpl, soResourceModuleImpl> ftKirbyResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImplVariable> ftKirbyModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<448, 797> ftKirbyAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<797, soMotionModuleImplMultiRes, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftKirbyMotionModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigGroups<3, 9, 3, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl> ftKirbyCollisionReflectorModuleBuildConfig;
typedef soCollisionCatchModuleBuildConfigWithSearch<soCollisionCatchModuleImpl, 0x254> ftKirbyCollisionCatchModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<8, soLinkModuleImpl> ftKirbyLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<448, soGeneralWorkBuildConfig<35, 18, 17>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftKirbyStatusModuleBuildConfig;
typedef soAreaModuleBuildConfigSized<0x3E0, soAreaModuleImpl> ftKirbyAreaModuleBuildConfig;
typedef soPhysicsModuleBuildConfigCap<0, soPhysicsModuleImpl> ftKirbyPhysicsModuleBuildConfig;
typedef soItemManageModuleBuildConfigCaps<7, 4, soItemManageModuleImpl> ftKirbyItemManageModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (wnKirbyHammer and the copy ability pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x12970, Fighter_Kirby> ftKirbyGenerateArticleManageModuleBuilder;

class ftKirbyBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftKirbyInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftKirbyHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftKirbyParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftKirbyResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftKirbyAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftKirbyModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftKirbyMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftKirbyCollisionReflectorModuleBuildConfig CollisionReflectorModuleBuildConfig;
    typedef ftKirbyCollisionCatchModuleBuildConfig CollisionCatchModuleBuildConfig;
    typedef ftKirbyLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftKirbyStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftKirbyAreaModuleBuildConfig AreaModuleBuildConfig;
    typedef ftKirbyPhysicsModuleBuildConfig PhysicsModuleBuildConfig;
    typedef ftKirbyItemManageModuleBuildConfig ItemManageModuleBuildConfig;
    typedef ftKirbyGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftKirby : public ftFighterBuilder<ftKirbyBuildConfig> {
    u8 unkTail[0x1C294 - sizeof(ftFighterBuilder<ftKirbyBuildConfig>)];
public:
    ftKirby(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
