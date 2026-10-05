#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Metaknight Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftMetaknightInsideEventManageModuleBuildConfig;
typedef soCollisionAttackModuleBuildConfig<soCollision::Category_Fighter, 5, 6, soCollisionAttackModuleImpl, 1, true, true> ftMetaknightCollisionAttackModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftMetaknightHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftMetaknightParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftMetaknightResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftMetaknightModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<290, 492> ftMetaknightAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<492, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftMetaknightMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftMetaknightCollisionShieldModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<12, soLinkModuleImpl> ftMetaknightLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<290, soGeneralWorkBuildConfig<28, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftMetaknightStatusModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (wnMetaknightMantle pool), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x2178, Fighter_MetaKnight> ftMetaknightGenerateArticleManageModuleBuilder;

class ftMetaknightBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftMetaknightInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftMetaknightCollisionAttackModuleBuildConfig CollisionAttackModuleBuildConfig;
    typedef ftMetaknightHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftMetaknightParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftMetaknightResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftMetaknightAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftMetaknightModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftMetaknightMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftMetaknightCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftMetaknightLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftMetaknightStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftMetaknightGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftMetaknight : public ftFighterBuilder<ftMetaknightBuildConfig> {
    u8 unkTail[0xA610 - sizeof(ftFighterBuilder<ftMetaknightBuildConfig>)];
public:
    ftMetaknight(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
