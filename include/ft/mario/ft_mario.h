#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Mario Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftMarioInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftMarioHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftMarioParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftMarioResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftMarioModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<281, 478> ftMarioAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<478, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftMarioMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftMarioCollisionShieldModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigGroups<3, 12, 3, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl> ftMarioCollisionReflectorModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftMarioLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<281, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftMarioStatusModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (wnMarioFireball/HugeFlame/Pump/Mantle pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x25AA8, Fighter_Mario> ftMarioGenerateArticleManageModuleBuilder;

class ftMarioBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftMarioInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftMarioHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftMarioParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftMarioResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftMarioAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftMarioModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftMarioMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftMarioCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftMarioCollisionReflectorModuleBuildConfig CollisionReflectorModuleBuildConfig;
    typedef ftMarioLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftMarioStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftMarioGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftMario : public ftFighterBuilder<ftMarioBuildConfig> {
public:
    ftMario(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
