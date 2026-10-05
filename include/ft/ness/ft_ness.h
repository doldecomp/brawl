#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Ness Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftNessInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftNessHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftNessParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftNessResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftNessModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<289, 490> ftNessAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<490, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftNessMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftNessCollisionShieldModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigGroups<3, 12, 3, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl> ftNessCollisionReflectorBaseModuleBuildConfig;
// HYPOTHESIS: the absorber builder (part kind 4) follows the reflector builder
typedef soCollisionShieldModuleBuildConfigGroups<4, 1, 1, soCollisionShieldEventPresenterAbsorber, soCollisionShieldModuleImpl> ftNessCollisionAbsorberModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigWithAbsorber<ftNessCollisionReflectorBaseModuleBuildConfig, ftNessCollisionAbsorberModuleBuildConfig> ftNessCollisionReflectorModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<8, soLinkModuleImpl> ftNessLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<289, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftNessStatusModuleBuildConfig;

// HYPOTHESIS: this fighter has its own kinetic transactor for changeKinetic (updateEnergy stays in ftKineticTransactor)
FT_KINETIC_TRANSACTOR(ftNessKineticTransactor);
typedef soKineticModuleBuildConfigMediator<soKineticModuleGenericImpl, ftKineticMediatorImplT<ftNessKineticTransactor, ftKineticTransactor> > ftNessKineticModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x42A0C, Fighter_Ness> ftNessGenerateArticleManageModuleBuilder;

class ftNessBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftNessInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftNessHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftNessParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftNessResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftNessAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftNessModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftNessMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftNessCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftNessCollisionReflectorModuleBuildConfig CollisionReflectorModuleBuildConfig;
    typedef ftNessLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftNessStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftNessKineticModuleBuildConfig KineticModuleBuildConfig;
    typedef ftNessGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftNess : public ftFighterBuilder<ftNessBuildConfig> {
    u8 unkTail[0x4AE28 - sizeof(ftFighterBuilder<ftNessBuildConfig>)];
public:
    ftNess(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
