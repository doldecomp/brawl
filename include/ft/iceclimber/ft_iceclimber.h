#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Popo Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftPopoInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftPopoHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftPopoParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftPopoResourceIdAccesserImpl, soResourceModuleImpl> ftPopoResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftPopoModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<289, 498> ftPopoAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<498, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftPopoMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftPopoCollisionShieldModuleBuildConfig;
typedef soGeneralWorkBuildConfig<66, 34, 3> ftPopoGeneralWorkBuildConfig;
typedef soLinkModuleBuildConfigCap<7, soLinkModuleImpl> ftPopoLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<289, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftPopoStatusModuleBuildConfig;

// HYPOTHESIS: this fighter has its own kinetic transactor (changeKinetic is in a later translation unit)
FT_KINETIC_TRANSACTOR(ftPopoKineticTransactor);
typedef soKineticModuleBuildConfigMediator<soKineticModuleGenericImpl, ftKineticMediatorImplT<ftPopoKineticTransactor> > ftPopoKineticModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x17ACC, Fighter_Popo> ftPopoGenerateArticleManageModuleBuilder;

class ftPopoBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftPopoInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftPopoHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftPopoParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftPopoResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftPopoAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftPopoModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftPopoMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftPopoCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftPopoGeneralWorkBuildConfig GeneralWorkBuildConfig;
    typedef ftPopoLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftPopoStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftPopoKineticModuleBuildConfig KineticModuleBuildConfig;
    typedef ftPopoGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftPopo : public ftFighterBuilder<ftPopoBuildConfig> {
    u8 unkTail[0x1FE50 - sizeof(ftFighterBuilder<ftPopoBuildConfig>)];
public:
    ftPopo(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
