#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Samus Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 10, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftSamusInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftSamusHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftSamusParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftSamusResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftSamusModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<301, 492> ftSamusAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<492, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftSamusMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftSamusCollisionShieldModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftSamusLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<301, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftSamusStatusModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (wnSamusCShot pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x1D7D4, Fighter_Samus> ftSamusGenerateArticleManageModuleBuilder;

class ftSamusBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftSamusInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftSamusHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftSamusParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftSamusResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftSamusAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftSamusModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftSamusMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftSamusCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftSamusLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftSamusStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftSamusGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftSamus : public ftFighterBuilder<ftSamusBuildConfig> {
    u8 unkTail[0x25C0C - sizeof(ftFighterBuilder<ftSamusBuildConfig>)];
public:
    ftSamus(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
