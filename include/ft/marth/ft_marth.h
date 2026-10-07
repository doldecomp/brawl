#pragma once

#include <ft/ft_fighter_builder.h>
#include <ft/marth/ft_marth_extend_param_accesser.h>
#include <sr/sr_common.h>
#include <so/so_photo_call_back.h>
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

typedef ftAnimCmdModuleSubBuildConfig<289, 501> ftMarthAnimCmdModuleSubBuildConfig;

class ftMarthBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftMarthInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftMarthHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftMarthParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftMarthResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftMarthAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftMarthModelModuleBuildConfig ModelModuleBuildConfig;
};

class ftMarth : public ftFighterBuilder<ftMarthBuildConfig>, public soPhotoCallBack {
    u8 unkTail[0x8574 - sizeof(ftFighterBuilder<ftMarthBuildConfig>) - sizeof(soPhotoCallBack)];
public:
    ftMarth(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
    virtual void photoMoved();
    virtual void photoExit();
    virtual bool notifyEventCollisionShieldCheck();
    virtual void notifyEventCollisionShield(soCollisionAttackModule* attackModule, float power, soCollisionLog* collisionLog, int groupIndex, float posX, float posY, soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(ftFighterBuilder<ftMarthBuildConfig>) == 0x8554, "Photo callback offset is wrong!");
static_assert(sizeof(ftMarth) == 0x8574, "Class is the wrong size!");
