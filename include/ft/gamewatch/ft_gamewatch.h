#pragma once

#include <ft/ft_fighter_builder.h>
#include <sr/sr_common.h>
#include <types.h>

////////////////////////////////////////
// GameWatch-only builder variants
////////////////////////////////////////

FT_DOL_POLY_BEGIN(soCollisionShieldEventPresenterAbsorber, 0x10);
    soCollisionShieldEventPresenterAbsorber(soModuleAccesser* acc);
FT_DOL_POLY_END;

// GameWatch has a soCollisionAbsorberModuleBuilder (1 part, 1 group; the shield builder with another presenter and part kind) after the
// reflector builder, which has no member slot of its own in soModuleAccesserBuilder. HYPOTHESIS: the 4 bytes after the reflector builder
// of the other fighters are the empty absorber builder; here it is folded into the reflector builder's storage (the ctor order is the same).
template <typename R, typename A>
class soCollisionReflectorModuleBuildConfigWithAbsorber {
public:
    typedef R ReflectorBuildConfig;
    typedef A AbsorberBuildConfig;
};

template <typename R, typename A>
class soCollisionReflectorModuleBuilder<soCollisionReflectorModuleBuildConfigWithAbsorber<R, A> > {
    soCollisionShieldModuleBuilder<R> m_reflectorBuilder;
    soCollisionShieldModuleBuilder<A> m_absorberBuilder;
public:
    soCollisionReflectorModuleBuilder(soModuleAccesser* acc, int taskId, gfTask::Category category) :
        m_reflectorBuilder(acc, taskId, category), m_absorberBuilder(acc, taskId, category) { }
    typename R::ModuleType* getModule() { return m_reflectorBuilder.getModule(); }
    typename A::ModuleType* getAbsorberModule() { return m_absorberBuilder.getModule(); }
};

template <typename R, typename A>
struct ftAbsorberModuleOf<soCollisionReflectorModuleBuilder<soCollisionReflectorModuleBuildConfigWithAbsorber<R, A> > > {
    static void* get(soCollisionReflectorModuleBuilder<soCollisionReflectorModuleBuildConfigWithAbsorber<R, A> >* b) { return b->getAbsorberModule(); }
};

////////////////////////////////////////
// GameWatch Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftGameWatchInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftGameWatchHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftGameWatchParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftGameWatchResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftGameWatchModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<313, 514> ftGameWatchAnimCmdModuleSubBuildConfig;
typedef soMotionModuleBuildConfig<514, soMotionModuleImpl, 2, 1, soTransitionModuleBuildConfig<ftMotionTransitionTypeList>, soMotionAnimObjCacheModuleBuildConfig<5, soMotionAnimObjCacheModuleImpl> > ftGameWatchMotionModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<2, 1, 1, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl> ftGameWatchCollisionShieldModuleBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<3, 20, 2, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl> ftGameWatchReflectorOnlyBuildConfig;
typedef soCollisionShieldModuleBuildConfigGroups<4, 1, 1, soCollisionShieldEventPresenterAbsorber, soCollisionShieldModuleImpl> ftGameWatchAbsorberBuildConfig;
typedef soCollisionReflectorModuleBuildConfigWithAbsorber<ftGameWatchReflectorOnlyBuildConfig, ftGameWatchAbsorberBuildConfig> ftGameWatchCollisionReflectorModuleBuildConfig;
typedef soLinkModuleBuildConfigCap<6, soLinkModuleImpl> ftGameWatchLinkModuleBuildConfig;
typedef soStatusModuleBuildConfig<313, soGeneralWorkBuildConfig<18, 14, 2>, 274, 71, soTransitionModuleBuildConfig<ftStatusTransitionTypeList> > ftGameWatchStatusModuleBuildConfig;

// HYPOTHESIS: this fighter has its own kinetic transactor (changeKinetic is in a later translation unit)
FT_KINETIC_TRANSACTOR(ftGameWatchKineticTransactor);
typedef soKineticModuleBuildConfigMediator<soKineticModuleGenericImpl, ftKineticMediatorImplT<ftGameWatchKineticTransactor, ftKineticTransactor> > ftGameWatchKineticModuleBuildConfig;

// HYPOTHESIS: soGenerateArticleManageModuleBuilder (weapon pools), not reconstructed yet
typedef ftOpaqueGenerateArticleManageModuleBuilder<0x1771C, Fighter_GameWatch> ftGameWatchGenerateArticleManageModuleBuilder;

class ftGameWatchBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftGameWatchInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftGameWatchHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftGameWatchParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftGameWatchResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftGameWatchAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftGameWatchModelModuleBuildConfig ModelModuleBuildConfig;
    typedef ftGameWatchMotionModuleBuildConfig MotionModuleBuildConfig;
    typedef ftGameWatchCollisionShieldModuleBuildConfig CollisionShieldModuleBuildConfig;
    typedef ftGameWatchCollisionReflectorModuleBuildConfig CollisionReflectorModuleBuildConfig;
    typedef ftGameWatchLinkModuleBuildConfig LinkModuleBuildConfig;
    typedef ftGameWatchStatusModuleBuildConfig StatusModuleBuildConfig;
    typedef ftGameWatchKineticModuleBuildConfig KineticModuleBuildConfig;
    typedef ftGameWatchGenerateArticleManageModuleBuilder GenerateArticleManageModuleBuilder;
};

class ftGameWatch : public ftFighterBuilder<ftGameWatchBuildConfig> {
    u8 unkTail[0x1FDE4 - sizeof(ftFighterBuilder<ftGameWatchBuildConfig>)];
public:
    ftGameWatch(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
