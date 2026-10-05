#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Ganon Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftGanonInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftGanonHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftGanonParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftGanonResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftGanonModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<290, 488> ftGanonAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<488, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftGanonMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftGanonCollisionShieldModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftGanonLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<290, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftGanonStatusModuleBuildConfig;

// HYPOTHESIS: this fighter has its own kinetic transactor (changeKinetic is in a later translation unit)
FT_KINETIC_TRANSACTOR(ftGanonKineticTransactor);
typedef soKineticModuleBuildConfigMediator<soKineticModuleGenericImpl, ftKineticMediatorImplT<ftGanonKineticTransactor> > ftGanonKineticModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x4630, Fighter_Ganon> ftGanonGenerateArticleManageModuleBuilder;

class ftGanonBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftGanonInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftGanonHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftGanonParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftGanonResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftGanonAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftGanonModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftGanonMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftGanonCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftGanonLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftGanonStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftGanonKineticModuleBuildConfig KineticModuleBuildConfig;
    typedef ftGanonGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftGanon : public ftFighterBuilder<ftGanonBuildConfig> {
    u8 unkC984[0xC9A8 - 0xC984];
public:
    ftGanon(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
