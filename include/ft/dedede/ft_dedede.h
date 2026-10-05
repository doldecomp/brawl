#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Dedede-only builder variants
////////////////////////////////////////

// Area module builder with another number of area instances (same code as soAreaModuleBuilder).
template <s32 NumInstances, typename T>
class soAreaModuleBuildConfigInstances {
public:
    typedef T ModuleType;
};

template <s32 NumInstances, typename T>
class soAreaModuleBuilder<soAreaModuleBuildConfigInstances<NumInstances, T> > : public soArraySelectHolder<1, soArrayVector<soAreaWind, 1>, soArrayNull<soAreaWind> > {
    T m_module;
    soAreaEnviromentElementCheckerImpl m_checker;
    soArrayVector<soAreaContactLog, 16> m_contactLogs;
    soArrayVector<soAreaInstance, NumInstances> m_instances;
    u32 m_pad;
public:
    soAreaModuleBuilder(soModuleAccesser* acc, u8 areaCategory, soEventObserverRegistrationDesc* regDesc) :
        soArraySelectHolder<1, soArrayVector<soAreaWind, 1>, soArrayNull<soAreaWind> >(1, 0),
        m_module(acc, areaCategory, &m_instances, &m_contactLogs, &m_checker, this->get(), regDesc, 8),
        m_checker(), m_contactLogs(0), m_instances(0) { }
    void* getModule() { return &m_module; }
};

// HYPOTHESIS: the item manage module takes the waddle dee search (ftDededeWaddledeeSearchImpl, in a later translation unit) and the
// item pick transactor as global objects in place of the shared null objects.
extern char g_ftDededeWaddledeeSearchImpl[];
extern char g_ftDededeItemPickTransactor[];

// Item manage module builder with other capacities.
template <s32 CapA, s32 CapB, typename T>
class soItemManageModuleBuildConfigCapsSearch {
public:
    typedef T ModuleType;
};

template <s32 CapA, s32 CapB, typename T>
class soItemManageModuleBuilder<soItemManageModuleBuildConfigCapsSearch<CapA, CapB, T> > : public soArraySelectHolder<1, soArrayVector<soItemInfo, CapA>, soArrayNull<soItemInfo> > {
    soArraySelectHolder<1, soArrayVector<soItemInfo, CapB>, soArrayNull<soItemInfo> > m_items2;
    T m_itemModule;
public:
    soItemManageModuleBuilder(soModuleAccesser* acc, void* itemNodeData) :
        soArraySelectHolder<1, soArrayVector<soItemInfo, CapA>, soArrayNull<soItemInfo> >(CapA, 0), m_items2(), m_itemModule(acc, this->get(), m_items2.get(), itemNodeData, g_ftDededeWaddledeeSearchImpl, g_ftDededeItemPickTransactor) { }
    T* getModule() { return &m_itemModule; }
};

////////////////////////////////////////
// Dedede Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftDededeInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftDededeHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftDededeParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftDededeResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftDededeModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<314, 535> ftDededeAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<535, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftDededeMotionModuleBuildConfig;
typedef soAreaModuleBuildConfigInstances<11, ftAreaModuleImpl> ftDededeAreaModuleBuildConfig;
typedef soItemManageModuleBuildConfigCapsSearch<7, 4, soItemManageModuleImpl> ftDededeItemManageModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftDededeCollisionShieldModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<7, soLinkModuleImpl> ftDededeLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<314, soGeneralWorkBuildConfig<18, 14, 11>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftDededeStatusModuleBuildConfig;
typedef soCollisionSearchModuleBuilder<soCollisionSearchModuleBuildConfig<soCollisionSearchModuleImpl> > ftDededeCollisionSearchModuleBuilder;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x3F000, Fighter_Dedede> ftDededeGenerateArticleManageModuleBuilder;

class ftDededeBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftDededeInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftDededeHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftDededeParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftDededeResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftDededeAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftDededeModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftDededeMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftDededeCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftDededeAreaModuleBuildConfig AreaModuleBuildConfig;
    typedef ftDededeItemManageModuleBuildConfig ItemManageModuleBuildConfig;
    typedef ftDededeLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftDededeStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftDededeCollisionSearchModuleBuilder CollisionSearchModuleBuilder;
    typedef ftDededeGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftDedede : public ftFighterBuilder<ftDededeBuildConfig> {
    u8 unkTail[0x4777C - sizeof(ftFighterBuilder<ftDededeBuildConfig>)];
public:
    ftDedede(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
