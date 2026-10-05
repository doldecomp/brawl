#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Luigi Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftLuigiInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftLuigiHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftLuigiParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftLuigiResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<11, 3, soModelModuleImpl> ftLuigiModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<285, 482> ftLuigiAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<482, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftLuigiMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftLuigiCollisionShieldModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigGroups<3, 12, 3, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl> ftLuigiCollisionReflectorModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftLuigiLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<285, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftLuigiStatusModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (wnLuigiNegativeZone pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x6000, Fighter_Luigi> ftLuigiGenerateArticleManageModuleBuilder;

class ftLuigiBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftLuigiInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftLuigiHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftLuigiParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftLuigiResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftLuigiAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftLuigiModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftLuigiMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftLuigiCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftLuigiCollisionReflectorModuleBuildConfig CollisionReflectorModuleBuildConfig;
    typedef ftLuigiLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftLuigiStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftLuigiGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftLuigi : public ftFighterBuilder<ftLuigiBuildConfig> {
public:
    ftLuigi(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
