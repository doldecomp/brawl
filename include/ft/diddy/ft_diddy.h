#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Diddy-only builder variants
////////////////////////////////////////

// HYPOTHESIS: Diddy's damage module uses ftDiddyDamageTransactorImpl (onDamageChangeStatusRequest lives in a later translation unit); its
// global instance is handed to the damage module where the other fighters pass the shared null object.
extern char g_ftDiddyDamageTransactorImpl[];
struct ftDiddyDamageTransactorTag {
    static void* get() { return g_ftDiddyDamageTransactorImpl; }
};

template <typename T, typename Tag>
class soDamageModuleBuildConfigWithTransactor {
public:
    typedef T ModuleType;
};

template <typename T, typename Tag>
class soDamageModuleBuilder<soDamageModuleBuildConfigWithTransactor<T, Tag> > : public soArraySelectHolder<1, soArrayVector<soDamage, 1>, soArrayNull<soDamage> > {
    T m_damageModule;
public:
    soDamageModuleBuilder(soModuleAccesser* acc, soEventObserverRegistrationDesc* regDesc) :
        soArraySelectHolder<1, soArrayVector<soDamage, 1>, soArrayNull<soDamage> >(1, 0), m_damageModule(acc, this->get(), g_soDamageModuleNullA, Tag::get(), regDesc) { }
    T* getModule() { return &m_damageModule; }
};

////////////////////////////////////////
// Diddy Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftDiddyInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftDiddyHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftDiddyParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftDiddyResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftDiddyModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<303, 507> ftDiddyAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<507, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftDiddyMotionModuleBuildConfig;
typedef soDamageModuleBuildConfigWithTransactor<soDamageModuleActor, ftDiddyDamageTransactorTag> ftDiddyDamageModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftDiddyCollisionShieldModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftDiddyLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<303, soGeneralWorkBuildConfig<18, 15, 29>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftDiddyStatusModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x1E400, Fighter_Diddy> ftDiddyGenerateArticleManageModuleBuilder;

class ftDiddyBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftDiddyInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftDiddyHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftDiddyParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftDiddyResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftDiddyAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftDiddyModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftDiddyMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftDiddyCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftDiddyDamageModuleBuildConfig DamageModuleBuildConfig;
    typedef ftDiddyLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftDiddyStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftDiddyGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftDiddy : public ftFighterBuilder<ftDiddyBuildConfig> {
    u8 unkTail[0x26884 - sizeof(ftFighterBuilder<ftDiddyBuildConfig>)];
public:
    ftDiddy(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
