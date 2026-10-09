#pragma once

#include <ft/ft_fighter_builder.h>
#include <so/so_photo_call_back.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Peach Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftPeachInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftPeachHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftPeachParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftPeachResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftPeachModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<287, 481> ftPeachAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<481, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftPeachMotionModuleBuildConfig;
typedef soPostureModuleBuildConfig<2, soPostureModuleImpl> ftPeachPostureModuleBuildConfig;
typedef soCollisionAttackModuleBuildConfig<soCollision::Category_Fighter, 7, 2, soCollisionAttackModuleImpl, 5, true, true> ftPeachCollisionAttackModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftPeachLinkModuleBuildConfig;
// HYPOTHESIS: term counts of the 20 status transition groups (differs from ftStatusTransitionTypeList)
typedef soTypeList<soIntToType<25>, soTypeList<soIntToType<6>, soTypeList<soIntToType<2>, soTypeList<soIntToType<1>, soTypeList<soIntToType<18>, soTypeList<soIntToType<3>, soTypeList<soIntToType<1>, soTypeList<soIntToType<2>, soTypeList<soIntToType<8>, soTypeList<soIntToType<2>, soTypeList<soIntToType<1>, soTypeList<soIntToType<6>, soTypeList<soIntToType<4>, soTypeList<soIntToType<1>, soTypeList<soIntToType<1>, soTypeList<soIntToType<2>, soTypeList<soIntToType<3>, soTypeList<soIntToType<2>, soTypeList<soIntToType<6>, soTypeList<soIntToType<1>, soTypeListNullType > > > > > > > > > > > > > > > > > > > > ftPeachStatusTransitionTypeList;
typedef soStatusModuleBuildConfig<287, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftPeachStatusTransitionTypeList> > ftPeachStatusModuleBuildConfig;
typedef soCollisionSearchModuleBuilder<soCollisionSearchModuleBuildConfig<soCollisionSearchModuleImpl> > ftPeachCollisionSearchModuleBuilder;

// HYPOTHESIS: this fighter has its own kinetic transactor (updateEnergy and changeKinetic)
FT_KINETIC_TRANSACTOR(ftPeachKineticTransactor);
typedef soKineticModuleBuildConfigMediator<soKineticModuleGenericImpl, ftKineticMediatorImplT<ftPeachKineticTransactor> > ftPeachKineticModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0xFEBC, Fighter_Peach> ftPeachGenerateArticleManageModuleBuilder;

class ftPeachBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftPeachInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftPeachHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftPeachParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftPeachResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftPeachAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftPeachModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftPeachMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftPeachPostureModuleBuildConfig PostureModuleBuildConfig;
    typedef ftPeachCollisionAttackModuleBuildConfig CollisionAttackModuleBuildConfig;
    typedef ftPeachLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftPeachStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftPeachCollisionSearchModuleBuilder CollisionSearchModuleBuilder;
    typedef ftPeachKineticModuleBuildConfig KineticModuleBuildConfig;
    typedef ftPeachGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftPeach : public ftFighterBuilder<ftPeachBuildConfig>, public soPhotoCallBack {
    // The photo callback starts at +0x186F0 in the native fighter.
    u8 unkTail[0x18710 - sizeof(ftFighterBuilder<ftPeachBuildConfig>) - sizeof(soPhotoCallBack)];
public:
    ftPeach(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
    void endFinalRequest();
};
static_assert(sizeof(ftFighterBuilder<ftPeachBuildConfig>) == 0x186F0, "ftPeach photo callback offset mismatch");
static_assert(sizeof(ftPeach) == 0x18710, "ftPeach size mismatch");
