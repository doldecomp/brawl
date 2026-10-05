#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Lucas Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftLucasInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftLucasHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftLucasParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftLucasResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftLucasModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<290, 491> ftLucasAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<491, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftLucasMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftLucasCollisionShieldModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigGroups<3, 14, 3, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl> ftLucasCollisionReflectorBaseModuleBuildConfig;
// HYPOTHESIS: the absorber builder (part kind 4) follows the reflector builder
typedef soCollisionShieldModuleBuildConfigGroups<4, 1, 1, soCollisionShieldEventPresenterAbsorber, soCollisionShieldModuleImpl> ftLucasCollisionAbsorberModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigWithAbsorber<ftLucasCollisionReflectorBaseModuleBuildConfig, ftLucasCollisionAbsorberModuleBuildConfig> ftLucasCollisionReflectorModuleBuildConfig;
typedef soStatusModuleBuildConfig<290, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftLucasStatusModuleBuildConfig;

// HYPOTHESIS: this fighter has its own kinetic transactor for changeKinetic (updateEnergy stays in ftKineticTransactor)
FT_KINETIC_TRANSACTOR(ftLucasKineticTransactor);
typedef soKineticModuleBuildConfigMediator<soKineticModuleGenericImpl, ftKineticMediatorImplT<ftLucasKineticTransactor, ftKineticTransactor> > ftLucasKineticModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x40814, Fighter_Lucas> ftLucasGenerateArticleManageModuleBuilder;

class ftLucasBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftLucasInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftLucasHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftLucasParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftLucasResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftLucasAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftLucasModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftLucasMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftLucasCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftLucasCollisionReflectorModuleBuildConfig CollisionReflectorModuleBuildConfig;
    typedef ftLucasStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftLucasKineticModuleBuildConfig KineticModuleBuildConfig;
    typedef ftLucasGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftLucas : public ftFighterBuilder<ftLucasBuildConfig> {
    u8 unkTail[0x48CC8 - sizeof(ftFighterBuilder<ftLucasBuildConfig>)];
public:
    ftLucas(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
