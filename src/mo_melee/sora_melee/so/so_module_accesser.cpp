#include <so/so_activate.h>
#include <so/so_module_accesser.h>
#include <types.h>

soModuleEnumeration::soModuleEnumeration(
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
    void* unusedParam)
{
    m_resourceModule = resourceModule;
    m_modelModule = modelModule;
    m_motionModule = motionModule;
    m_postureModule = postureModule;
    m_groundModule = groundModule;
    m_situationModule = situationModule;
    m_teamModule = teamModule;
    m_collisionAttackModule = collisionAttackModule;
    m_collisionHitModule = collisionHitModule;
    m_collisionShieldModule = collisionShieldModule;
    m_collisionReflectorModule = collisionReflectorModule;
    m_collisionAbsorberModule = collisionAbsorberModule;
    m_collisionCatchModule = collisionCatchModule;
    m_collisionSearchModule = collisionSearchModule;
    m_damageModule = damageModule;
    m_catchModule = catchModule;
    m_captureModule = captureModule;
    m_stopModule = stopModule;
    m_turnModule = turnModule;
    m_shakeModule = shakeModule;
    m_soundModule = soundModule;
    m_linkModule = linkModule;
    m_visibilityModule = visibilityModule;
    m_controllerModule = controllerModule;
    m_cameraModule = cameraModule;
    m_workManageModule = workManageModule;
    m_debugModule = debugModule;
    m_animCmdModule = animCmdModule;
    m_statusModule = statusModule;
    m_generalTermDecideModule = generalTermDecideModule;
    m_switchDecideModule = switchDecideModule;
    m_kineticModule = kineticModule;
    m_eventManageModule = eventManageModule;
    m_generateArticleManageModule = generateArticleManageModule;
    m_effectModule = effectModule;
    m_comboModule = comboModule;
    m_areaModule = areaModule;
    m_territoryModule = territoryModule;
    m_targetSearchModule = targetSearchModule;
    m_physicsModule = physicsModule;
    m_slopeModule = slopeModule;
    m_shadowModule = shadowModule;
    m_itemManageModule = itemManageModule;
    m_colorBlendModule = colorBlendModule;
    m_jostleModule = jostleModule;
    m_abnormalModule = abnormalModule;
    m_slowModule = slowModule;
    m_reflectModule = reflectModule;
    m_heapModule = heapModule;
    m_paramCustomizeModule = paramCustomizeModule;
    m_glowModule = glowModule;
}

soModuleAccesser::soModuleAccesser() :
    soActivatable(true),
    m_stageObject(nullptr),
    m_moduleEnumeration(),
    m_enumerationStart(&m_moduleEnumeration) { }

soModuleAccesser::soModuleAccesser(
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
    void* glowModule) :
        soActivatable(true),
        m_stageObject(stageObject),
        m_moduleEnumeration(
            resourceModule,
            modelModule,
            motionModule,
            postureModule,
            groundModule,
            situationModule,
            teamModule,
            collisionAttackModule,
            collisionHitModule,
            collisionShieldModule,
            collisionReflectorModule,
            collisionAbsorberModule,
            collisionCatchModule,
            collisionSearchModule,
            damageModule,
            catchModule,
            captureModule,
            stopModule,
            turnModule,
            shakeModule,
            soundModule,
            linkModule,
            visibilityModule,
            controllerModule,
            cameraModule,
            workManageModule,
            debugModule,
            animCmdModule,
            statusModule,
            generalTermDecideModule,
            switchDecideModule,
            kineticModule,
            eventManageModule,
            generateArticleManageModule,
            effectModule,
            comboModule,
            areaModule,
            territoryModule,
            targetSearchModule,
            physicsModule,
            slopeModule,
            shadowModule,
            itemManageModule,
            colorBlendModule,
            jostleModule,
            abnormalModule,
            slowModule,
            reflectModule,
            heapModule,
            paramCustomizeModule,
            glowModule
        ),
        m_enumerationStart(&m_moduleEnumeration) { }

soModuleAccesser::~soModuleAccesser() { }

void soModuleAccesser::activate() {
    setActive(true);
    m_enumerationStart = &m_moduleEnumeration;
}

void soModuleAccesser::deactivate() {
    setActive(false);
    m_enumerationStart = &soModuleEnumeration::NullObject;
}
