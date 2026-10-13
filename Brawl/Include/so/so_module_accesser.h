#pragma once

#include <StaticAssert.h>
#include <so/anim/so_anim_cmd_module_impl.h>
#include <so/collision/so_collision_attack_module_impl.h>
#include <so/collision/so_collision_hit_module_impl.h>
#include <so/collision/so_collision_search_module_impl.h>
#include <so/collision/so_collision_shield_module_impl.h>
#include <so/color/so_color_blend_module_impl.h>
#include <so/controller/so_controller_module_impl.h>
#include <so/damage/so_damage_module_impl.h>
#include <so/effect/so_effect_module_impl.h>
#include <so/area/so_area_module_impl.h>
#include <so/ground/so_ground_module_impl.h>
#include <so/model/so_model_module_impl.h>
#include <so/motion/so_motion_module_impl.h>
#include <so/posture/so_posture_module_impl.h>
#include <so/resource/so_resource_module_impl.h>
#include <so/shadow/so_shadow_module_impl.h>
#include <so/situation/so_situation_module_impl.h>
#include <so/slow/so_slow_module_impl.h>
#include <so/sound/so_sound_module_impl.h>
#include <so/status/so_status_module_impl.h>
#include <so/kinetic/so_kinetic_module_impl.h>
#include <so/event/so_event_manage_module_impl.h>
#include <so/work/so_work_manage_module_impl.h>
#include <so/param/so_param_customize_module_impl.h>
#include <so/camera/so_camera_module_impl.h>
#include <so/link/so_link_module_impl.h>
#include <so/visibility/so_visibility_module_impl.h>
#include <so/capture/so_capture_module_impl.h>
#include <so/item/so_item_manage_module_impl.h>
#include <so/turn/so_turn_module_impl.h>
#include <so/stop/so_stop_module_impl.h>
#include <so/so_activate.h>
#include <types.h>

class StageObject;

class soModuleEnumeration {
public:
    soModuleEnumeration(
        soResourceModule* resourceModule,
        soModelModule* modelModule,
        soMotionModule* motionModule,
        soPostureModule* postureModule,
        soGroundModule* groundModule,
        soSituationModule* situationModule,
        void* teamModule,
        soCollisionAttackModule* collisionAttackModule,
        soCollisionHitModule* collisionHitModule,
        soCollisionShieldModule* collisionShieldModule,
        soCollisionShieldModule* collisionReflectorModule,
        soCollisionShieldModule* collisionAbsorberModule,
        void* collisionCatchModule,
        soCollisionSearchModule* collisionSearchModule,
        soDamageModule* damageModule,
        void* catchModule,
        void* captureModule,
        soStopModule* stopModule,
        void* turnModule,
        void* shakeModule,
        soSoundModule* soundModule,
        soLinkModule* linkModule,
        soVisibilityModule* visibilityModule,
        soControllerModule* controllerModule,
        soCameraModule* cameraModule,
        soWorkManageModule* workManageModule,
        void* debugModule,
        soAnimCmdModule* animCmdModule,
        soStatusModule* statusModule,
        void* generalTermDecideModule,
        void* switchDecideModule,
        soKineticModule* kineticModule,
        soEventManageModule* eventManageModule,
        void* generateArticleManageModule,
        soEffectModule* effectModule,
        void* comboModule,
        soAreaModule* areaModule,
        void* territoryModule,
        void* targetSearchModule,
        void* physicsModule,
        void* slopeModule,
        soShadowModule* shadowModule,
        soItemManageModule* itemManageModule,
        soColorBlendModule* colorBlendModule,
        void* jostleModule,
        void* abnormalModule,
        soSlowModule* slowModule,
        void* reflectModule,
        void* heapModule,
        soParamCustomizeModule* paramCustomizeModule,
        void* glowModule,
        void* unusedParam = nullptr
    );

    static const soModuleEnumeration NullObject;

    soModuleEnumeration() {
        m_resourceModule = NullObject.m_resourceModule,
        m_modelModule = NullObject.m_modelModule,
        m_motionModule = NullObject.m_motionModule,
        m_postureModule = NullObject.m_postureModule,
        m_groundModule = NullObject.m_groundModule,
        m_situationModule = NullObject.m_situationModule,
        m_teamModule = NullObject.m_teamModule,
        m_collisionAttackModule = NullObject.m_collisionAttackModule,
        m_collisionHitModule = NullObject.m_collisionHitModule,
        m_collisionShieldModule = NullObject.m_collisionShieldModule,
        m_collisionReflectorModule = NullObject.m_collisionReflectorModule,
        m_collisionAbsorberModule = NullObject.m_collisionAbsorberModule,
        m_collisionCatchModule = NullObject.m_collisionCatchModule,
        m_collisionSearchModule = NullObject.m_collisionSearchModule,
        m_damageModule = NullObject.m_damageModule,
        m_catchModule = NullObject.m_catchModule,
        m_captureModule = NullObject.m_captureModule,
        m_stopModule = NullObject.m_stopModule,
        m_turnModule = NullObject.m_turnModule,
        m_shakeModule = NullObject.m_shakeModule,
        m_soundModule = NullObject.m_soundModule,
        m_linkModule = NullObject.m_linkModule,
        m_visibilityModule = NullObject.m_visibilityModule,
        m_controllerModule = NullObject.m_controllerModule,
        m_cameraModule = NullObject.m_cameraModule,
        m_workManageModule = NullObject.m_workManageModule,
        m_debugModule = NullObject.m_debugModule,
        m_animCmdModule = NullObject.m_animCmdModule,
        m_statusModule = NullObject.m_statusModule,
        m_generalTermDecideModule = NullObject.m_generalTermDecideModule,
        m_switchDecideModule = NullObject.m_switchDecideModule,
        m_kineticModule = NullObject.m_kineticModule,
        m_eventManageModule = NullObject.m_eventManageModule,
        m_generateArticleManageModule = NullObject.m_generateArticleManageModule,
        m_effectModule = NullObject.m_effectModule,
        m_comboModule = NullObject.m_comboModule,
        m_areaModule = NullObject.m_areaModule,
        m_territoryModule = NullObject.m_territoryModule,
        m_targetSearchModule = NullObject.m_targetSearchModule,
        m_physicsModule = NullObject.m_physicsModule,
        m_slopeModule = NullObject.m_slopeModule,
        m_shadowModule = NullObject.m_shadowModule,
        m_itemManageModule = NullObject.m_itemManageModule,
        m_colorBlendModule = NullObject.m_colorBlendModule,
        m_jostleModule = NullObject.m_jostleModule,
        m_abnormalModule = NullObject.m_abnormalModule,
        m_slowModule = NullObject.m_slowModule,
        m_reflectModule = NullObject.m_reflectModule,
        m_heapModule = NullObject.m_heapModule,
        m_paramCustomizeModule = NullObject.m_paramCustomizeModule,
        m_glowModule = NullObject.m_glowModule;
    }

    soResourceModule* m_resourceModule;
    soModelModule* m_modelModule;
    soMotionModule* m_motionModule;
    soPostureModule* m_postureModule;
    soGroundModule* m_groundModule;
    soSituationModule* m_situationModule;
    void* m_teamModule;
    soCollisionAttackModule* m_collisionAttackModule;
    soCollisionHitModule* m_collisionHitModule;
    soCollisionShieldModule* m_collisionShieldModule;
    soCollisionShieldModule* m_collisionReflectorModule;
    soCollisionShieldModule* m_collisionAbsorberModule;
    void* m_collisionCatchModule;
    soCollisionSearchModule* m_collisionSearchModule;
    soDamageModule* m_damageModule;
    void* m_catchModule;
    void* m_captureModule;
    soStopModule* m_stopModule;
    void* m_turnModule;
    void* m_shakeModule;
    soSoundModule* m_soundModule;
    soLinkModule* m_linkModule; // +0x54
    soVisibilityModule* m_visibilityModule;
    soControllerModule* m_controllerModule;
    soCameraModule* m_cameraModule;
    soWorkManageModule* m_workManageModule;
    void* m_debugModule;
    soAnimCmdModule* m_animCmdModule;
    soStatusModule* m_statusModule;
    void* m_generalTermDecideModule;
    void* m_switchDecideModule;
    soKineticModule* m_kineticModule; // +0x7C
    soEventManageModule* m_eventManageModule;
    void* m_generateArticleManageModule;
    soEffectModule* m_effectModule;
    void* m_comboModule;
    soAreaModule* m_areaModule;
    void* m_territoryModule;
    void* m_targetSearchModule;
    void* m_physicsModule;
    void* m_slopeModule;
    soShadowModule* m_shadowModule;
    soItemManageModule* m_itemManageModule;
    soColorBlendModule* m_colorBlendModule;
    void* m_jostleModule;
    void* m_abnormalModule;
    soSlowModule* m_slowModule;
    void* m_reflectModule;
    void* m_heapModule;
    soParamCustomizeModule* m_paramCustomizeModule;
    void* m_glowModule;
};
static_assert(sizeof(soModuleEnumeration) == 204, "Class is wrong size!");

class soModuleAccesser : private soNull, private soActivatable {
public:
    StageObject* m_stageObject;
    soModuleEnumeration m_moduleEnumeration;
    const soModuleEnumeration* m_enumerationStart; // +0xD8

    soModuleAccesser();
    soModuleAccesser(
        StageObject* stageObject,
        soResourceModule* resourceModule,
        soModelModule* modelModule,
        soMotionModule* motionModule,
        soPostureModule* postureModule,
        soGroundModule* groundModule,
        soSituationModule* situationModule,
        void* teamModule,
        soCollisionAttackModule* collisionAttackModule,
        soCollisionHitModule* collisionHitModule,
        soCollisionShieldModule* collisionShieldModule,
        soCollisionShieldModule* collisionReflectorModule,
        soCollisionShieldModule* collisionAbsorberModule,
        void* collisionCatchModule,
        soCollisionSearchModule* collisionSearchModule,
        soDamageModule* damageModule,
        void* catchModule,
        void* captureModule,
        soStopModule* stopModule,
        void* turnModule,
        void* shakeModule,
        soSoundModule* soundModule,
        soLinkModule* linkModule,
        soVisibilityModule* visibilityModule,
        soControllerModule* controllerModule,
        soCameraModule* cameraModule,
        soWorkManageModule* workManageModule,
        void* debugModule,
        soAnimCmdModule* animCmdModule,
        soStatusModule* statusModule,
        void* generalTermDecideModule,
        void* switchDecideModule,
        soKineticModule* kineticModule,
        soEventManageModule* eventManageModule,
        void* generateArticleManageModule,
        soEffectModule* effectModule,
        void* comboModule,
        soAreaModule* areaModule,
        void* territoryModule,
        void* targetSearchModule,
        void* physicsModule,
        void* slopeModule,
        soShadowModule* shadowModule,
        soItemManageModule* itemManageModule,
        soColorBlendModule* colorBlendModule,
        void* jostleModule,
        void* abnormalModule,
        soSlowModule* slowModule,
        void* reflectModule,
        void* heapModule,
        soParamCustomizeModule* paramCustomizeModule,
        void* glowModule
    );
    virtual ~soModuleAccesser();

    void activate();
    void deactivate();

    StageObject& getStageObject() const {
        return *m_stageObject;
    }

    soResourceModule& getResourceModule() const {
        return *m_enumerationStart->m_resourceModule;
    }

    soModelModule& getModelModule() const
    {
        return *m_enumerationStart->m_modelModule;
    }

    soMotionModule& getMotionModule() const {
        return *m_enumerationStart->m_motionModule;
    }

    soPostureModule& getPostureModule() const
    {
        return *m_enumerationStart->m_postureModule;
    }

    soGroundModule& getGroundModule() const
    {
        return *m_enumerationStart->m_groundModule;
    }

    soShadowModule& getShadowModule() const
    {
        return *m_enumerationStart->m_shadowModule;
    }

    soSituationModule& getSituationModule() const
    {
        return *m_enumerationStart->m_situationModule;
    }

    soCollisionAttackModule& getCollisionAttackModule() const
    {
        return *m_enumerationStart->m_collisionAttackModule;
    }

    soCollisionHitModule& getCollisionHitModule() const
    {
        return *m_enumerationStart->m_collisionHitModule;
    }

    soCollisionShieldModule& getCollisionShieldModule() const
    {
        return *m_enumerationStart->m_collisionShieldModule;
    }

    soCollisionShieldModule& getCollisionReflectorModule() const
    {
        return *m_enumerationStart->m_collisionReflectorModule;
    }

    soCollisionShieldModule& getCollisionAbsorberModule() const
    {
        return *m_enumerationStart->m_collisionAbsorberModule;
    }

    soCollisionSearchModule& getCollisionSearchModule() const
    {
        return *m_enumerationStart->m_collisionSearchModule;
    }

    soDamageModule& getDamageModule() const
    {
        return *m_enumerationStart->m_damageModule;
    }

    soStopModule& getStopModule() const {
        return *m_enumerationStart->m_stopModule;
    }

    soSoundModule& getSoundModule() const
    {
        return *m_enumerationStart->m_soundModule;
    }

    soLinkModule& getLinkModule() const {
        return *m_enumerationStart->m_linkModule;
    }

    soVisibilityModule& getVisibilityModule() const
    {
        return *m_enumerationStart->m_visibilityModule;
    }

    soControllerModule& getControllerModule() const
    {
        return *m_enumerationStart->m_controllerModule;
    }

    soCameraModule& getCameraModule() const {
        return *m_enumerationStart->m_cameraModule;
    }

    soWorkManageModule& getWorkManageModule() const {
        return *m_enumerationStart->m_workManageModule;
    }

    soAnimCmdModule& getAnimCmdModule()  const
    {
        return *m_enumerationStart->m_animCmdModule;
    }

    soStatusModule& getStatusModule() const
    {
        return *m_enumerationStart->m_statusModule;
    }

    soKineticModule& getKineticModule() const
    {
        return *m_enumerationStart->m_kineticModule;
    }

    soEventManageModule& getEventManageModule() const
    {
        return *m_enumerationStart->m_eventManageModule;
    }

    soEffectModule& getEffectModule() const {
        return *m_enumerationStart->m_effectModule;
    }

    soAreaModule& getAreaModule() const {
        return *m_enumerationStart->m_areaModule;
    }

    soSlowModule& getSlowModule() const
    {
        return *m_enumerationStart->m_slowModule;
    }

    soItemManageModule& getItemManageModule() const
    {
        return *m_enumerationStart->m_itemManageModule;
    }

    soColorBlendModule& getColorBlendModule() const
    {
        return *m_enumerationStart->m_colorBlendModule;
    }

    soParamCustomizeModule& getParamCustomizeModule() const
    {
        return *m_enumerationStart->m_paramCustomizeModule;
    }
};
static_assert(sizeof(soModuleAccesser) == 0xE0, "Class is wrong size!");

class soModuleAccesserNull : public soModuleAccesser {

};

extern soModuleAccesserNull g_soModuleAccesserNull;

// TODO: Move this to a new header once its full definition is decomped
#ifndef MATCHING
template <class BC>
class soModuleAccesserBuilder {
    BC t;
};
#endif
