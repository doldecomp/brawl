#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// ToonLink Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftToonLinkInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftToonLinkHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftToonLinkParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftToonLinkResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftToonLinkModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<284, 484> ftToonLinkAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<484, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftToonLinkMotionModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftToonLinkLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<284, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftToonLinkStatusModuleBuildConfig;
typedef soCollisionSearchModuleBuilder<soCollisionSearchModuleBuildConfig<soCollisionSearchModuleImpl> > ftToonLinkCollisionSearchModuleBuilder;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x11CE4, Fighter_ToonLink> ftToonLinkGenerateArticleManageModuleBuilder;

class ftToonLinkBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftToonLinkInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftToonLinkHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftToonLinkParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftToonLinkResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftToonLinkAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftToonLinkModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftToonLinkMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftToonLinkLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftToonLinkStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftToonLinkCollisionSearchModuleBuilder CollisionSearchModuleBuilder;
    typedef ftToonLinkGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftToonLink : public ftFighterBuilder<ftToonLinkBuildConfig> {
    u8 unk1A374[0x1A39C - 0x1A374];
public:
    ftToonLink(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
