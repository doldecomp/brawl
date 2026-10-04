#pragma once

// soModuleAccesserBuilder<BC> / ftModuleAccesserBuilder<BC>: the storage and construction order of every
// module of a fighter. Offsets in the comments are relative to the start of the builder (+0x194 in Fighter).
// A BuildConfig class (see ftCommonBuildConfig) selects the module implementations and capacities.

#include <ft/builder/ft_module_builders.h>
#include <so/so_module_accesser_builder.h>
#include <so/so_inside_event_manage_module_builder.h>
#include <ft/ft_param_customize_module_impl.h>
#include <ft/ft_resource_id_accesser_impl.h>

// Size checks of the pieces. Fails to compile if a member layout is wrong.
#define FT_ASSERT_SIZE(T, N) typedef char ft_assert_size_##__LINE__[(sizeof(T) == (N)) ? 1 : -1]

// Storage for a part that has not been reconstructed yet (keeps the layout of the rest right).
template <u32 N>
struct ftUnknownBuilderPart {
    u8 m_data[N];
};

////////////////////////////////////////
// default build configuration shared by all fighters (override per character if it differs)
////////////////////////////////////////

class ftCommonBuildConfig {
public:
    typedef soGroundModuleBuildConfig<1, soGroundModuleImpl> GroundModuleBuildConfig;
    typedef soPostureModuleBuildConfig<1, soPostureModuleImpl> PostureModuleBuildConfig;
    typedef soCollisionAttackModuleBuildConfig<soCollision::Category_Fighter, 5, 2, soCollisionAttackModuleImpl, 5, true, true>
        CollisionAttackModuleBuildConfig;
    typedef soCollisionHitModuleBuildConfig<soCollision::Category_Fighter, 20, 1, soCollisionHitModuleImpl, 0x3ff, true>
        CollisionHitModuleBuildConfig;
    typedef soCollisionShieldModuleBuildConfig<2, 2, soCollisionShieldEventPresenterShield, soCollisionShieldModuleImpl>
        CollisionShieldModuleBuildConfig;
    typedef soCollisionShieldModuleBuildConfig<3, 20, soCollisionShieldEventPresenterReflector, soCollisionShieldModuleImpl>
        CollisionReflectorModuleBuildConfig;
    typedef soCollisionCatchModuleBuildConfig<soCollisionCatchModuleImpl> CollisionCatchModuleBuildConfig;
    typedef soSituationModuleBuildConfig<soSituationModuleImpl> SituationModuleBuildConfig;
    typedef soCatchModuleBuildConfig<1, soCatchModuleImpl> CatchModuleBuildConfig;
    typedef soCaptureModuleBuildConfig<soCaptureModuleImpl> CaptureModuleBuildConfig;
    typedef soStopModuleBuildConfig<ftStopModuleImpl> StopModuleBuildConfig;
    typedef soTurnModuleBuildConfig<soTurnModuleImpl> TurnModuleBuildConfig;
    typedef soVisibilityModuleBuildConfig<soVisibilityModuleImpl, 2> VisibilityModuleBuildConfig;
    typedef soWorkManageModuleBuildConfig<soWorkManageModuleImpl> WorkManageModuleBuildConfig;
    typedef soSlopeModuleBuildConfig<0, 1, soSlopeModuleImpl> SlopeModuleBuildConfig;
    typedef soShadowModuleBuildConfig<soShadowModuleImpl> ShadowModuleBuildConfig;
    typedef soDamageModuleBuildConfig<soDamageModuleActor> DamageModuleBuildConfig;
    typedef soShakeModuleBuildConfig<4, soShakeModuleImpl> ShakeModuleBuildConfig;
    typedef soSoundModuleBuildConfig<soSoundModuleImpl> SoundModuleBuildConfig;
    typedef soLinkModuleBuildConfig<soLinkModuleImpl> LinkModuleBuildConfig;
    typedef soControllerModuleBuildConfig<ftControllerModuleImpl> ControllerModuleBuildConfig;
    typedef soCameraModuleBuildConfig<soCameraModuleImpl> CameraModuleBuildConfig;
    typedef soEffectModuleBuildConfig<soEffectModuleImpl> EffectModuleBuildConfig;
    typedef soPhysicsModuleBuildConfig<soPhysicsModuleImpl> PhysicsModuleBuildConfig;
    typedef soItemManageModuleBuildConfig<soItemManageModuleImpl> ItemManageModuleBuildConfig;
};

extern char g_soCollisionAbsorberModuleNull[];
extern char g_soCollisionSearchModuleNull[];
extern char g_soDebugModuleNull[];
extern char g_soGeneralTermDecideModuleNull[];
extern char g_soSwitchDecideModuleNull[];
extern char g_soGenerateArticleManageModuleNull[];
extern char g_soTerritoryModuleNull[];
extern char g_soTargetSearchModuleNull[];
extern char g_soReflectModuleNull[];

template <class BC>
class soModuleAccesserBuilder : public utUnCopyable {
public:
    soInsideEventManageModuleBuilder<typename BC::InsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> unk194; // +0x0
    soModuleAccesser m_moduleAccsr;                                                                        // +0x9D0
    soHeapModuleBuilder<typename BC::HeapModuleBuildConfig> m_heapModuleBuilder;                           // +0xAB0
    soParamCustomizeModuleBuilder<typename BC::ParamCustomizeModuleBuildConfig> m_paramCustomizeModuleBuilder; // +0xAC8
    soResourceModuleBuilder<typename BC::ResourceModuleBuildConfig> m_resourceModuleBuilder;               // +0x115C
    soModelModuleBuilder<typename BC::ModelModuleBuildConfig> m_modelModuleBuilder;                        // +0x1180
    ftUnknownBuilderPart<0x394> m_motionBuilder;                                                           // +0x1440
    soPostureModuleBuilder<typename BC::PostureModuleBuildConfig> m_postureModuleBuilder;                  // +0x17D4
    soGroundModuleBuilder<typename BC::GroundModuleBuildConfig> m_groundModuleBuilder;                     // +0x1888
    soSituationModuleBuilder<typename BC::SituationModuleBuildConfig> m_situationModuleBuilder;                                                               // +0x1930
    ftUnknownBuilderPart<0x74> m_teamBuilder;                                                              // +0x196C
    soCollisionAttackModuleBuilder<typename BC::CollisionAttackModuleBuildConfig> m_attackModuleBuilder;   // +0x19E0
    soCollisionHitModuleBuilder<typename BC::CollisionHitModuleBuildConfig> m_hitModuleBuilder;            // +0x209C
    soCollisionShieldModuleBuilder<typename BC::CollisionShieldModuleBuildConfig> m_shieldModuleBuilder;   // +0x29F8
    soCollisionShieldModuleBuilder<typename BC::CollisionReflectorModuleBuildConfig> m_reflectorModuleBuilder; // +0x2DA0
    soCollisionCatchModuleBuilder<typename BC::CollisionCatchModuleBuildConfig> m_collisionCatchModuleBuilder; // +0x380C
    soDamageModuleBuilder<typename BC::DamageModuleBuildConfig> m_damageModuleBuilder;                     // +0x3A70
    soCatchModuleBuilder<typename BC::CatchModuleBuildConfig> m_catchModuleBuilder;                                                                       // +0x3C20
    soCaptureModuleBuilder<typename BC::CaptureModuleBuildConfig> m_captureModuleBuilder;                                                                   // +0x3C84
    soStopModuleBuilder<typename BC::StopModuleBuildConfig> m_stopModuleBuilder;                                                                         // +0x3CB8
    soTurnModuleBuilder<typename BC::TurnModuleBuildConfig> m_turnModuleBuilder;                                                                         // +0x3CDC
    soShakeModuleBuilder<typename BC::ShakeModuleBuildConfig> m_shakeModuleBuilder;                        // +0x3D14
    soSoundModuleBuilder<typename BC::SoundModuleBuildConfig> m_soundModuleBuilder;                        // +0x3DAC
    soLinkModuleBuilder<typename BC::LinkModuleBuildConfig> m_linkModuleBuilder;                           // +0x3E1C
    soVisibilityModuleBuilder<typename BC::VisibilityModuleBuildConfig> m_visibilityModuleBuilder;                                                             // +0x3FE8
    soControllerModuleBuilder<typename BC::ControllerModuleBuildConfig> m_controllerModuleBuilder;         // +0x4018
    soCameraModuleBuilder<typename BC::CameraModuleBuildConfig> m_cameraModuleBuilder;                     // +0x473C
    soWorkManageModuleBuilder<typename BC::WorkManageModuleBuildConfig> m_workManageModuleBuilder;                                                             // +0x47B0
    ftUnknownBuilderPart<0xF4> m_animCmdBuilder;                                                           // +0x47E4
    ftUnknownBuilderPart<0xEB8> m_statusBuilder;                                                           // +0x48D8
    ftUnknownBuilderPart<0x308> m_kineticBuilder;                                                          // +0x5790
    ftUnknownBuilderPart<0x1E8> m_generalWorkBuilder;                                                      // +0x5A98
    soEffectModuleBuilder<typename BC::EffectModuleBuildConfig> m_effectModuleBuilder;                     // +0x5C80
    ftUnknownBuilderPart<0x30> m_comboModule;                                                              // +0x5E24
    ftUnknownBuilderPart<0x374> m_areaBuilder;                                                             // +0x5E54
    soPhysicsModuleBuilder<typename BC::PhysicsModuleBuildConfig> m_physicsModuleBuilder;                  // +0x61C8
    soSlopeModuleBuilder<typename BC::SlopeModuleBuildConfig> m_slopeModuleBuilder;                                                                       // +0x628C
    soShadowModuleBuilder<typename BC::ShadowModuleBuildConfig> m_shadowModuleBuilder;                                                                     // +0x630C
    soItemManageModuleBuilder<typename BC::ItemManageModuleBuildConfig> m_itemManageModuleBuilder;         // +0x6354
    ftUnknownBuilderPart<0x154> m_colorBlendModule;                                                        // +0x6464
    ftUnknownBuilderPart<0x4C> m_jostleModule;                                                             // +0x65B8
    ftUnknownBuilderPart<0x68> m_abnormalModule;                                                           // +0x6604
    ftUnknownBuilderPart<0x3C> m_slowModule;                                                               // +0x666C
    ftUnknownBuilderPart<0x180> m_glowModule;                                                              // +0x66A8
    // end: +0x6828

    soModuleAccesserBuilder(const ftFighterBuildData& fbd, StageObject* owner) :
        m_moduleAccsr(
            owner,
            (soResourceModule*)((u8*)&m_resourceModuleBuilder + sizeof(typename BC::ResourceModuleBuildConfig::IdAccesserType)), // soResourceModuleBuilder::getModule() is not inlined by MWCC
            (soModelModule*)((u8*)&m_modelModuleBuilder + sizeof(soArrayVector<soModelNodeSetUp, BC::ModelModuleBuildConfig::NodeSetUpCap>) + sizeof(soArrayVector<soModelVirtualNode, BC::ModelModuleBuildConfig::VirtualNodeCap>)),
            (soMotionModule*)((u8*)&m_motionBuilder + 0x224),
            (soPostureModule*)m_postureModuleBuilder.getModule(),
            (soGroundModule*)m_groundModuleBuilder.getModule(),
            (soSituationModule*)m_situationModuleBuilder.getModule(),
            (void*)((u8*)&m_teamBuilder + 0x30),
            (soCollisionAttackModule*)ftBuilderModule<__typeof__(m_attackModuleBuilder)>::get(&m_attackModuleBuilder),
            (soCollisionHitModule*)ftBuilderModule<__typeof__(m_hitModuleBuilder)>::get(&m_hitModuleBuilder),
            (soCollisionShieldModule*)m_shieldModuleBuilder.getModule(),
            (soCollisionShieldModule*)m_reflectorModuleBuilder.getModule(),
            (soCollisionShieldModule*)g_soCollisionAbsorberModuleNull,
            (void*)m_collisionCatchModuleBuilder.getModule(),
            (soCollisionSearchModule*)g_soCollisionSearchModuleNull,
            (soDamageModule*)m_damageModuleBuilder.getModule(),
            (void*)m_catchModuleBuilder.getModule(),
            (void*)m_captureModuleBuilder.getModule(),
            (soStopModule*)m_stopModuleBuilder.getModule(),
            (void*)m_turnModuleBuilder.getModule(),
            (void*)m_shakeModuleBuilder.getModule(),
            (soSoundModule*)m_soundModuleBuilder.getModule(),
            (soLinkModule*)m_linkModuleBuilder.getModule(),
            (soVisibilityModule*)m_visibilityModuleBuilder.getModule(),
            (soControllerModule*)m_controllerModuleBuilder.getModule(),
            (soCameraModule*)m_cameraModuleBuilder.getModule(),
            (soWorkManageModule*)m_workManageModuleBuilder.getModule(),
            (void*)g_soDebugModuleNull,
            (soAnimCmdModule*)&m_animCmdBuilder,
            (soStatusModule*)((u8*)&m_statusBuilder + 0xE08),
            (void*)g_soGeneralTermDecideModuleNull,
            (void*)g_soSwitchDecideModuleNull,
            (soKineticModule*)&m_kineticBuilder,
            (soEventManageModule*)((u8*)&unk194 + 0xB8), // soInsideEventManageModuleBuilder::m_module (specialization has no getModule())
            (void*)g_soGenerateArticleManageModuleNull,
            (soEffectModule*)m_effectModuleBuilder.getModule(),
            (void*)&m_comboModule,
            (soAreaModule*)((u8*)&m_areaBuilder + 0x10),
            (void*)g_soTerritoryModuleNull,
            (void*)g_soTargetSearchModuleNull,
            (void*)m_physicsModuleBuilder.getModule(),
            (void*)m_slopeModuleBuilder.getModule(),
            (soShadowModule*)m_shadowModuleBuilder.getModule(),
            (soItemManageModule*)m_itemManageModuleBuilder.getModule(),
            (soColorBlendModule*)&m_colorBlendModule,
            (void*)&m_jostleModule,
            (void*)&m_abnormalModule,
            (soSlowModule*)&m_slowModule,
            (void*)g_soReflectModuleNull,
            (void*)&m_heapModuleBuilder,
            (soParamCustomizeModule*)&m_paramCustomizeModuleBuilder,
            (void*)&m_glowModule),
        m_heapModuleBuilder(fbd),
        m_paramCustomizeModuleBuilder(&m_moduleAccsr),
        m_resourceModuleBuilder(
            fbd.getMdlResId(),
            fbd.getAnmResId(),
            fbd.getResGroupNo(),
            &m_moduleAccsr
        ),
        m_modelModuleBuilder(
            &m_moduleAccsr,
            fbd.getModelExtendNodeTable(),
            &g_soEventObserverRegistrationDescNull,
            fbd.getModelScale()
        ),
        m_postureModuleBuilder(&m_moduleAccsr, &g_soEventObserverRegistrationDescNull),
        m_groundModuleBuilder(&m_moduleAccsr, fbd.getGroundConditionChecker()),
        m_situationModuleBuilder(m_moduleAccsr.getEventManageModule().getManageId(), &m_moduleAccsr, &g_soEventObserverRegistrationDescNull),
        m_attackModuleBuilder(&m_moduleAccsr, owner->m_taskId, owner->m_taskCategory, &g_soEventObserverRegistrationDescNull),
        m_hitModuleBuilder(&m_moduleAccsr, owner->m_taskId, owner->m_taskCategory, &g_soEventObserverRegistrationDescNull),
        m_shieldModuleBuilder(&m_moduleAccsr, owner->m_taskId, owner->m_taskCategory),
        m_reflectorModuleBuilder(&m_moduleAccsr, owner->m_taskId, owner->m_taskCategory),
        m_collisionCatchModuleBuilder(&m_moduleAccsr, owner->m_taskId, owner->m_taskCategory, &g_soEventObserverRegistrationDescNull),
        m_damageModuleBuilder(&m_moduleAccsr, &g_soEventObserverRegistrationDescNull),
        m_catchModuleBuilder(&m_moduleAccsr),
        m_captureModuleBuilder(&m_moduleAccsr),
        m_stopModuleBuilder(&m_moduleAccsr),
        m_turnModuleBuilder(&m_moduleAccsr),
        m_shakeModuleBuilder(&m_moduleAccsr, fbd.getShakeData()),
        m_soundModuleBuilder(&m_moduleAccsr, fbd.getSoundIdExchanger(), &g_soEventObserverRegistrationDescNull),
        m_linkModuleBuilder(m_moduleAccsr.getEventManageModule().getManageId()),
        m_visibilityModuleBuilder(&m_moduleAccsr, fbd.getVisibilityData()),
        m_controllerModuleBuilder(&m_moduleAccsr, m_moduleAccsr.getEventManageModule().getManageId()),
        m_cameraModuleBuilder(&m_moduleAccsr, (soSet<soCameraRange>*)fbd.getCameraRangeSet(), (soSet<soCameraClipSphere>*)fbd.getCameraClipSphereSet(), &g_soEventObserverRegistrationDescNull),
        m_workManageModuleBuilder(&m_moduleAccsr, fbd.getParamAccesser()),
        m_effectModuleBuilder(&m_moduleAccsr, fbd.getEffectNodeData(), fbd.getEffectEmitData(), fbd.getEffectCommonData(), fbd.getEffectScreenData(), &g_soEventObserverRegistrationDescNull),
        m_physicsModuleBuilder(&m_moduleAccsr, fbd.getIkData()),
        m_slopeModuleBuilder(&m_moduleAccsr, fbd.getSlopeAngleLimit()),
        m_shadowModuleBuilder(&m_moduleAccsr),
        m_itemManageModuleBuilder(&m_moduleAccsr, fbd.getItemNodeData()) {
    }

    ~soModuleAccesserBuilder() { }
    soModuleAccesser* getModuleAccesser() { return &m_moduleAccsr; }
};

template <typename BC>
class ftModuleAccesserBuilder : public soModuleAccesserBuilder<BC> {
public:
    soArrayContractibleTable<const soStatusData> unkTable;
    ftAnimCmdModuleSubBuilder<typename BC::AnimCmdModuleSubBuildConfig> unkAnimCmdModuleSubBuilder;

    ftModuleAccesserBuilder(const ftFighterBuildData& fbd, StageObject* owner) : soModuleAccesserBuilder<BC>(fbd, owner) {
    }
};
