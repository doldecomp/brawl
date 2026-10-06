#pragma once

#include <ft/ft_fighter_builder.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/robot/ft_robot_article_pools.h>
#include <sr/sr_common.h>
#include <types.h>

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftRobotInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftRobotHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftRobotParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftRobotResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftRobotModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<286, 487> ftRobotAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<487, soMotionModuleImpl, 3, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftRobotMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftRobotCollisionShieldModuleBuildConfig;
typedef soCollisionReflectorModuleBuildConfigGroups<3, 17, 3, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl> ftRobotCollisionReflectorModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftRobotLinkModuleBuildConfig;
typedef soPhysicsModuleBuildConfigCap<0, soPhysicsModuleImpl> ftRobotPhysicsModuleBuildConfig;
typedef soStatusModuleBuildConfig<286, soGeneralWorkBuildConfig<18, 14, 8>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftRobotStatusModuleBuildConfig;

typedef ftRobotArticleManageModuleBuilder ftRobotGenerateArticleManageModuleBuilder;

class ftRobotBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftRobotInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftRobotHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftRobotParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftRobotResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftRobotAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftRobotModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftRobotMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftRobotCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftRobotCollisionReflectorModuleBuildConfig CollisionReflectorModuleBuildConfig;
    typedef ftRobotLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftRobotPhysicsModuleBuildConfig PhysicsModuleBuildConfig;
    typedef ftRobotStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftRobotGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftRobot : public ftFighterBuilder<ftRobotBuildConfig> {
    soArrayContractibleTable<const soStatusData> m_statusTable; // 0x12290
    ftData* m_commonData; // 0x122a0
public:
    virtual void onActivate();
    virtual void notifyEventOnDamage(soDamage* damage, bool, soModuleAccesser* acc);

    ftRobot(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};

static_assert(sizeof(ftRobot) == 0x122A4, "Robot class size is wrong!");

static_assert(sizeof(ftFighterBuilder<ftRobotBuildConfig>) == 0x12290, "Robot builder layout is wrong!");
