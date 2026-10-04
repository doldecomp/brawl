#pragma once

#include <ft/ft_fighter_builder.h>
#include <ft/marth/ft_marth_extend_param_accesser.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// Marth Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftMarthInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftMarthHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftMarthParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftMarthResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftMarthModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<288, 501> ftMarthAnimCmdModuleSubBuildConfig;

class ftMarthBuildConfig {
public:
    typedef ftMarthInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftMarthHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftMarthParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftMarthResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftMarthAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftMarthModelModuleBuildConfig ModelModuleBuildConfig;
};

class ftMarth : public ftFighterBuilder<ftMarthBuildConfig> {
    u8 unk8554[0x8574 - 0x8554];
public:
    ftMarth(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
