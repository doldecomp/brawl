#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Pikmin Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftPikminInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftPikminHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftPikminParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftPikminResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftPikminModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<284, 480> ftPikminAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<480, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftPikminMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftPikminCollisionShieldModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<13, soLinkModuleImpl> ftPikminLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<284, soGeneralWorkBuildConfig<19, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftPikminStatusModuleBuildConfig;

// HYPOTHESIS: this fighter has its own kinetic transactor (changeKinetic; updateEnergy stays in ftKineticTransactor)
FT_KINETIC_TRANSACTOR(ftPikminKineticTransactor);
typedef soKineticModuleBuildConfigMediator<soKineticModuleGenericImpl, ftKineticMediatorImplT<ftPikminKineticTransactor, ftKineticTransactor> > ftPikminKineticModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x17878, Fighter_Pikmin> ftPikminGenerateArticleManageModuleBuilder;

class ftPikminBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftPikminInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftPikminHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftPikminParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftPikminResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftPikminAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftPikminModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftPikminMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftPikminCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftPikminLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftPikminStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftPikminKineticModuleBuildConfig KineticModuleBuildConfig;
    typedef ftPikminGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftPikmin : public ftFighterBuilder<ftPikminBuildConfig> {
    u8 unkTail[0x20130 - sizeof(ftFighterBuilder<ftPikminBuildConfig>)];
public:
    ftPikmin(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
