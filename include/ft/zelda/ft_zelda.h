#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Zelda Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftZeldaInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftZeldaHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftZeldaParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftZeldaResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftZeldaModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<284, 480> ftZeldaAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<480, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftZeldaMotionModuleBuildConfig;
typedef soCollisionAttackModuleBuildConfig<soCollision::Category_Fighter, 5, 10, soCollisionAttackModuleImpl, 5, true, true> ftZeldaCollisionAttackModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftZeldaCollisionShieldModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigGroups<3, 13, 3, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl> ftZeldaCollisionReflectorModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftZeldaLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<284, soGeneralWorkBuildConfig<34, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftZeldaStatusModuleBuildConfig;
typedef soCollisionSearchModuleBuilder<soCollisionSearchModuleBuildConfig<soCollisionSearchModuleImpl> > ftZeldaCollisionSearchModuleBuilder;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0xFF40, Fighter_Zelda> ftZeldaGenerateArticleManageModuleBuilder;

class ftZeldaBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftZeldaInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftZeldaHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftZeldaParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftZeldaResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftZeldaAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftZeldaModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftZeldaMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftZeldaCollisionAttackModuleBuildConfig CollisionAttackModuleBuildConfig;
    typedef ftZeldaCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftZeldaCollisionReflectorModuleBuildConfig CollisionReflectorModuleBuildConfig;
    typedef ftZeldaLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftZeldaStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftZeldaCollisionSearchModuleBuilder CollisionSearchModuleBuilder;
    typedef ftZeldaGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftZelda : public ftFighterBuilder<ftZeldaBuildConfig> {
    u8 unk18650[0x18678 - 0x18650];
public:
    ftZelda(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
