#pragma once

#include <ft/ft_fighter_builder.h>
#include <ft/ft_common_data_accesser.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Zako (Subspace Emissary Primid) Build Configuration
// All four Zako fighters (Boy, Girl, Child, Ball) share these module configurations; each has its own
// BuildConfig class, so that the builders are instantiated once per fighter.
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftZakoInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftZakoHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftZakoParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftZakoResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftZakoModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<280, 463> ftZakoAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<463, soMotionModuleImpl, 2, 2, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftZakoMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftZakoCollisionShieldModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigGroups<3, 20, 2, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl> ftZakoCollisionReflectorModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftZakoLinkModuleBuildConfig;
typedef soAreaModuleBuildConfig<ftAreaModuleImpl, 3> ftZakoAreaModuleBuildConfig;
typedef soStatusModuleBuildConfig<280, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftZakoStatusModuleBuildConfig;

class ftZakoBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftZakoInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftZakoHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftZakoParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftZakoResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftZakoAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftZakoModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftZakoMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftZakoCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftZakoCollisionReflectorModuleBuildConfig CollisionReflectorModuleBuildConfig;
    typedef ftZakoLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftZakoAreaModuleBuildConfig AreaModuleBuildConfig;
    typedef ftZakoStatusModuleBuildConfig StatusModuleBuildConfig;
};

class ftZakoBoyBuildConfig : public ftZakoBuildConfig { };
class ftZakoGirlBuildConfig : public ftZakoBuildConfig { };
class ftZakoChildBuildConfig : public ftZakoBuildConfig { };
class ftZakoBallBuildConfig : public ftZakoBuildConfig { };

#define FT_ZAKO_CLASS(NAME)                                                 \
    class ftZako##NAME : public ftFighterBuilder<ftZako##NAME##BuildConfig> { \
    public:                                                                 \
        ftZako##NAME(s32 entryId,                                           \
                     Heaps::HeapType instHeap,                              \
                     Heaps::HeapType nwModelInstHeap,                       \
                     Heaps::HeapType nwMotionInstHeap);                     \
        virtual bool checkTransitionStatus(u32 status);                     \
        virtual void onActivate();                                          \
        virtual bool isHeartSwapEnableCondition();                          \
        virtual bool setMetal(bool setStatus, float health, int unk3);      \
    };

FT_ZAKO_CLASS(Boy)
FT_ZAKO_CLASS(Girl)
FT_ZAKO_CLASS(Child)
FT_ZAKO_CLASS(Ball)
