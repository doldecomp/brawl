#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Donkey Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftDonkeyInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftDonkeyHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftDonkeyParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftDonkeyResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftDonkeyModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<309, 516> ftDonkeyAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<516, soMotionModuleImpl, 4, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftDonkeyMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftDonkeyCollisionShieldModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftDonkeyLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<309, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftDonkeyStatusModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0xA0B0, Fighter_Donkey> ftDonkeyGenerateArticleManageModuleBuilder;

class ftDonkeyBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftDonkeyInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftDonkeyHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftDonkeyParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftDonkeyResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftDonkeyAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftDonkeyModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftDonkeyMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftDonkeyCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftDonkeyLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftDonkeyStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftDonkeyGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftDonkey : public ftFighterBuilder<ftDonkeyBuildConfig> {
    u8 unkTail[0x1259C - sizeof(ftFighterBuilder<ftDonkeyBuildConfig>)];
public:
    ftDonkey(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
