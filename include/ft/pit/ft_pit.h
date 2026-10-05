#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Pit Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftPitInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftPitHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftPitParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftPitResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftPitModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<289, 500> ftPitAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<500, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftPitMotionModuleBuildConfig;
typedef soCollisionHitModuleBuildConfig<soCollision::Category_Fighter, 11, 1, soCollisionHitModuleImpl, 0x3ff, true> ftPitCollisionHitModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigGroups<3, 14, 4, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl> ftPitCollisionReflectorModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftPitLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<289, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftPitStatusModuleBuildConfig;

// HYPOTHESIS: this fighter has its own kinetic transactor (updateEnergy and changeKinetic)
FT_KINETIC_TRANSACTOR(ftPitKineticTransactor);
typedef soKineticModuleBuildConfigMediator<soKineticModuleGenericImpl, ftKineticMediatorImplT<ftPitKineticTransactor> > ftPitKineticModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x2163C, Fighter_Pit> ftPitGenerateArticleManageModuleBuilder;

class ftPitBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftPitInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftPitHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftPitParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftPitResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftPitAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftPitModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftPitMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftPitCollisionHitModuleBuildConfig CollisionHitModuleBuildConfig;
    typedef ftPitCollisionReflectorModuleBuildConfig CollisionReflectorModuleBuildConfig;
    typedef ftPitLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftPitStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftPitKineticModuleBuildConfig KineticModuleBuildConfig;
    typedef ftPitGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftPit : public ftFighterBuilder<ftPitBuildConfig> {
    u8 unkTail[0x297B8 - sizeof(ftFighterBuilder<ftPitBuildConfig>)];
public:
    ftPit(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
