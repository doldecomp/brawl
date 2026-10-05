#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Fox Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftFoxInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftFoxHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftFoxParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftFoxResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<10, 3, soModelModuleImpl> ftFoxModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<288, 498> ftFoxAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<498, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftFoxMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftFoxCollisionShieldModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigGroups<3, 15, 3, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl> ftFoxCollisionReflectorModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<7, soLinkModuleImpl> ftFoxLinkModuleBuildConfig;
typedef soCollisionHitModuleBuildConfig<soCollision::Category_Fighter, 13, 1, soCollisionHitModuleImpl, 0x3ff, true> ftFoxCollisionHitModuleBuildConfig;
typedef soStatusModuleBuildConfig<288, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftFoxStatusModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (wnFoxIllusion pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x14CD0, Fighter_Fox> ftFoxGenerateArticleManageModuleBuilder;

class ftFoxBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftFoxInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftFoxHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftFoxParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftFoxResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftFoxAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftFoxModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftFoxMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftFoxCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftFoxCollisionReflectorModuleBuildConfig CollisionReflectorModuleBuildConfig;
    typedef ftFoxLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftFoxCollisionHitModuleBuildConfig CollisionHitModuleBuildConfig;
    typedef ftFoxStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftFoxGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftFox : public ftFighterBuilder<ftFoxBuildConfig> {
public:
    ftFox(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
