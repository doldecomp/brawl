#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// PokeLizardon Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftPokeLizardonInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftPokeLizardonHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftPokeLizardonParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftPokeLizardonResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftPokeLizardonModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<281, 477> ftPokeLizardonAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<477, soMotionModuleImpl, 3, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftPokeLizardonMotionModuleBuildConfig;
typedef soCollisionHitModuleBuildConfig<soCollision::Category_Fighter, 16, 1, soCollisionHitModuleImpl, 0x3ff, true> ftPokeLizardonCollisionHitModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftPokeLizardonCollisionShieldModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftPokeLizardonLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<281, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftPokeLizardonStatusModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0xFDF0, Fighter_PokeLizardon> ftPokeLizardonGenerateArticleManageModuleBuilder;

class ftPokeLizardonBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftPokeLizardonInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftPokeLizardonHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftPokeLizardonParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftPokeLizardonResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftPokeLizardonAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftPokeLizardonModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftPokeLizardonMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftPokeLizardonCollisionHitModuleBuildConfig CollisionHitModuleBuildConfig;
    typedef ftPokeLizardonCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftPokeLizardonLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftPokeLizardonStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftPokeLizardonGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftPokeLizardon : public ftFighterBuilder<ftPokeLizardonBuildConfig> {
    u8 unkTail[0x17FDC - sizeof(ftFighterBuilder<ftPokeLizardonBuildConfig>)];
public:
    ftPokeLizardon(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
