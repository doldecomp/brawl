#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Pikachu Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftPikachuInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftPikachuHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftPikachuParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftPikachuResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftPikachuModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<288, 486> ftPikachuAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<486, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftPikachuMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftPikachuCollisionShieldModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftPikachuLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<288, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftPikachuStatusModuleBuildConfig;

// HYPOTHESIS: this fighter has its own kinetic transactor (updateEnergy and changeKinetic)
FT_KINETIC_TRANSACTOR(ftPikachuKineticTransactor);
typedef soKineticModuleBuildConfigMediator<soKineticModuleGenericImpl, ftKineticMediatorImplT<ftPikachuKineticTransactor> > ftPikachuKineticModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x22AE8, Fighter_Pikachu> ftPikachuGenerateArticleManageModuleBuilder;

class ftPikachuBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftPikachuInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftPikachuHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftPikachuParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftPikachuResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftPikachuAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftPikachuModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftPikachuMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftPikachuCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftPikachuLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftPikachuStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftPikachuKineticModuleBuildConfig KineticModuleBuildConfig;
    typedef ftPikachuGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftPikachu : public ftFighterBuilder<ftPikachuBuildConfig> {
    u8 unkTail[0x2AE48 - sizeof(ftFighterBuilder<ftPikachuBuildConfig>)];
public:
    ftPikachu(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
