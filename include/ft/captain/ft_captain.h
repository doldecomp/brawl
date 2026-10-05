#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Captain Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftCaptainInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftCaptainHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftCaptainParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftCaptainResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftCaptainModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<290, 491> ftCaptainAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<491, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftCaptainMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftCaptainCollisionShieldModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<12, soLinkModuleImpl> ftCaptainLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<290, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftCaptainStatusModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (wnCaptainBlueFalcon pool), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x4118, Fighter_Captain> ftCaptainGenerateArticleManageModuleBuilder;

class ftCaptainBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftCaptainInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftCaptainHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftCaptainParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftCaptainResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftCaptainAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftCaptainModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftCaptainMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftCaptainCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftCaptainLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftCaptainStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftCaptainGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftCaptain : public ftFighterBuilder<ftCaptainBuildConfig> {
    u8 unkTail[0xC5C8 - sizeof(ftFighterBuilder<ftCaptainBuildConfig>)];
public:
    ftCaptain(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
