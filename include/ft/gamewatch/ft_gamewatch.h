#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// GameWatch Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftGameWatchInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftGameWatchHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftGameWatchParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftGameWatchResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftGameWatchModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<313, 514> ftGameWatchAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<514, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftGameWatchMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftGameWatchCollisionShieldModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigGroups<3, 20, 2, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl> ftGameWatchCollisionReflectorBaseModuleBuildConfig;
// HYPOTHESIS: the absorber builder (part kind 4) follows the reflector builder
typedef soCollisionShieldModuleBuildConfigGroups<4, 1, 1, soCollisionShieldEventPresenterAbsorber, soCollisionShieldModuleImpl> ftGameWatchCollisionAbsorberModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigWithAbsorber<ftGameWatchCollisionReflectorBaseModuleBuildConfig, ftGameWatchCollisionAbsorberModuleBuildConfig> ftGameWatchCollisionReflectorModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftGameWatchLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<313, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftGameWatchStatusModuleBuildConfig;

// HYPOTHESIS: this fighter has its own kinetic transactor (changeKinetic is in a later translation unit)
FT_KINETIC_TRANSACTOR(ftGameWatchKineticTransactor);
typedef soKineticModuleBuildConfigMediator<soKineticModuleGenericImpl, ftKineticMediatorImplT<ftGameWatchKineticTransactor, ftKineticTransactor> > ftGameWatchKineticModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x1771C, Fighter_GameWatch> ftGameWatchGenerateArticleManageModuleBuilder;

class ftGameWatchBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftGameWatchInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftGameWatchHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftGameWatchParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftGameWatchResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftGameWatchAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftGameWatchModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftGameWatchMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftGameWatchCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftGameWatchCollisionReflectorModuleBuildConfig CollisionReflectorModuleBuildConfig;
    typedef ftGameWatchLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftGameWatchStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftGameWatchKineticModuleBuildConfig KineticModuleBuildConfig;
    typedef ftGameWatchGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftGameWatch : public ftFighterBuilder<ftGameWatchBuildConfig> {
    u8 unkTail[0x1FDE4 - sizeof(ftFighterBuilder<ftGameWatchBuildConfig>)];
public:
    ftGameWatch(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
