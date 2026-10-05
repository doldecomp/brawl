#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Lucario-only builder variants
////////////////////////////////////////

// HYPOTHESIS: ftLucarioParamCustomizeModule is an ftParamCustomizeModuleImpl with the attack power overrides (the aura).
// Opaque stand-in (same size as the base): the constructor and destructor are not defined here.
class ftLucarioParamCustomizeModule : public ftParamCustomizeModuleImpl {
public:
    ftLucarioParamCustomizeModule(soModuleAccesser* acc);
    virtual ~ftLucarioParamCustomizeModule();
};

////////////////////////////////////////
// Lucario Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftLucarioInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftLucarioHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftLucarioParamCustomizeModule> ftLucarioParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftLucarioResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftLucarioModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<293, 491> ftLucarioAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<491, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftLucarioMotionModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftLucarioLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<293, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftLucarioStatusModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x801C, Fighter_Lucario> ftLucarioGenerateArticleManageModuleBuilder;

class ftLucarioBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftLucarioInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftLucarioHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftLucarioParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftLucarioResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftLucarioAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftLucarioModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftLucarioMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftLucarioLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftLucarioStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftLucarioGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftLucario : public ftFighterBuilder<ftLucarioBuildConfig> {
    u8 unkTail[0x10548 - sizeof(ftFighterBuilder<ftLucarioBuildConfig>)];
public:
    ftLucario(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
