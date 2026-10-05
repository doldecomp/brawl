#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Falco Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftFalcoInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftFalcoHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftFalcoParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftFalcoResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<10, 3, soModelModuleImpl> ftFalcoModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<285, 492> ftFalcoAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<492, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftFalcoMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftFalcoCollisionShieldModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigGroups<3, 15, 3, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl> ftFalcoCollisionReflectorModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<7, soLinkModuleImpl> ftFalcoLinkModuleBuildConfig;
typedef soCollisionHitModuleBuildConfig<soCollision::Category_Fighter, 13, 1, soCollisionHitModuleImpl, 0x3ff, true> ftFalcoCollisionHitModuleBuildConfig;
typedef soStatusModuleBuildConfig<285, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftFalcoStatusModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (wnFalcoIllusion pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x15040, Fighter_Falco> ftFalcoGenerateArticleManageModuleBuilder;

class ftFalcoBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftFalcoInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftFalcoHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftFalcoParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftFalcoResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftFalcoAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftFalcoModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftFalcoMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftFalcoCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftFalcoCollisionReflectorModuleBuildConfig CollisionReflectorModuleBuildConfig;
    typedef ftFalcoLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftFalcoCollisionHitModuleBuildConfig CollisionHitModuleBuildConfig;
    typedef ftFalcoStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftFalcoGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftFalco : public ftFighterBuilder<ftFalcoBuildConfig> {
    u8 unk1D06C[0x1D0E4 - 0x1D06C];
public:
    ftFalco(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
