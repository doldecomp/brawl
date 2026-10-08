// Yoshi Egg status movement, clatter countdown, and collision handling.
// HYPOTHESIS: Unnamed virtual calls below retain their observed slots and argument order.
#include <ft/ft_kinetic_energy.h>
#include <ft/ft_owner.h>
#include <ft/fighter.h>
#include <ft/ft_status_uniq_process_yoshi_egg.h>
#include <gf/gf_task.h>
#include <mt/mt_prng.h>
#include <so/collision/so_collision_log.h>
#include <so/motion/so_motion_change_param.h>
#include <so/link/so_link_module_impl.h>
#include <so/posture/so_posture_module_simple.h>
#include <so/so_external_value_accesser.h>
#include <so/so_value_accesser.h>
#include <so/stageobject.h>
#include <types.h>

ftStatusUniqProcessYoshiEgg g_ftStatusUniqProcessYoshiEgg;

namespace {
enum {
    WorkFloat04 = 0x21000004,
    WorkFloat05 = 0x21000005,
    WorkFloat06 = 0x21000006,
    WorkFloat07 = 0x21000007,
    WorkFloat08 = 0x21000008,
    WorkFlag10 = 0x22000010,
};

#define NATIVE_VT(obj) (*(u32**)(obj))

inline float workGetFloat(soWorkManageModule* work, u32 id) {
    typedef float (*Call)(soWorkManageModule*, u32);
    return ((Call)NATIVE_VT(work)[0x38 / 4])(work, id);
}

inline void workSetFloat(soWorkManageModule* work, float value, u32 id) {
    typedef void (*Call)(soWorkManageModule*, float, u32);
    ((Call)NATIVE_VT(work)[0x3C / 4])(work, value, id);
}

inline bool workIsFlag(soWorkManageModule* work, u32 id) {
    typedef bool (*Call)(soWorkManageModule*, u32);
    return ((Call)NATIVE_VT(work)[0x4C / 4])(work, id);
}

inline void workOnFlag(soWorkManageModule* work, u32 id) {
    typedef void (*Call)(soWorkManageModule*, u32);
    ((Call)NATIVE_VT(work)[0x50 / 4])(work, id);
}
#undef NATIVE_VT
}

void ftStatusUniqProcessYoshiEgg::initStatus(soModuleAccesser* moduleAccesser) {
    // +0x0C is posture; native vtable slot +0x2C returns LR.
    soPostureModule& posture = moduleAccesser->getPostureModule();
    typedef float (*GetLr)(soPostureModule*);
    const float lr = ((GetLr)(*(u32**)(&posture))[0x2C / 4])(&posture);
    const float initialX = soValueAccesser::getConstantFloat(moduleAccesser, 0xD65, 0) * lr;
    const float initialY = soValueAccesser::getConstantFloat(moduleAccesser, 0xD66, 0);

    soKineticModule& kinetic = moduleAccesser->getKineticModule();
    // Native calls changeKinetic(0, moduleAccesser) before looking up energies.
    kinetic.changeKinetic(0, moduleAccesser);
    ftKineticEnergyController& controller =
        dynamic_cast<ftKineticEnergyController&>(*kinetic.getEnergy(2));
    ftKineticEnergyGravity& gravity =
        dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));

    const float gravityScale = soValueAccesser::getConstantFloat(moduleAccesser, 0xD72, 0);
    float damagePercent = moduleAccesser->getDamageModule().getDamage(0);
    if (damagePercent > 100.0f) {
        damagePercent = 100.0f;
    }
    const float percent = (1.0f - gravityScale) * (damagePercent * 0.01f);
    const float accelScale = (1.0f - percent) *
                             soValueAccesser::getConstantFloat(moduleAccesser, 0xBD3, 0);
    controller.m_speed.m_x = initialX;
    controller.m_speed.m_y = 0.0f;
    controller.m_accelMul = accelScale;
    gravity.m_speedY = initialY;

    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    workSetFloat(&work, accelScale, WorkFloat04);
    // RTTI descriptors identify StageObject as the source and Fighter as the
    // target; Fighter::getOwner is confirmed at vtable offset +0x2EC.
    Fighter& fighter = dynamic_cast<Fighter&>(moduleAccesser->getStageObject());
    const float ownerMultiplier = fighter.getOwner()->getYoshiEggTimeMul();
    const float animTime = soValueAccesser::getConstantFloat(moduleAccesser, 0xD6A, 0) * ownerMultiplier;
    const float animRate = soValueAccesser::getConstantFloat(moduleAccesser, 0xD6B, 0);
    const float animBlend = soValueAccesser::getConstantFloat(moduleAccesser, 0xD6C, 0);
    soControllerModule& controllerModule = moduleAccesser->getControllerModule();
    // Native controller vslot +0xC8 is startClatter; register args are
    // (0, -1, 0, false) after the three float values.
    // MATCH-ONLY: the shared u8 declaration would narrow native r5=-1 to 255.
    typedef void (*StartClatterNative)(soControllerModule*, float, float, float, int, int, u32, bool);
    ((StartClatterNative)(*(u32**)(&controllerModule))[0xC8 / 4])(
        &controllerModule, animTime, animRate, animBlend, 0, -1, 0, false);

    // The native link vslot +0xA8 is getParentLr(index); posture +0x30
    // sets LR, +0x54 updates Y rotation LR, +0x60 reads scale, +0x64 sets it.
    soLinkModule& link = moduleAccesser->getLinkModule();
    const float parentLr = link.getParentLr(0);
    posture.setLr(parentLr);
    posture.updateRotYLr();
    workSetFloat(&work, soValueAccesser::getConstantFloat(moduleAccesser, 0xD69, 0), WorkFloat06);
    const float postureBase = posture.getScale();
    workSetFloat(&work, postureBase, WorkFloat07);
    const float postureScale = soValueAccesser::getConstantFloat(moduleAccesser, 0xD68, 0);
    posture.setScale((1.0f - postureScale) * postureBase);

    soModelModule& model = moduleAccesser->getModelModule();
    typedef int (*SlotIntReturn)(void*, int);
    const int modelResult = ((SlotIntReturn)(*(u32**)(&model))[0x8C / 4])(&model, 0x130);
    const float baseScale = soValueAccesser::getConstantFloat(moduleAccesser, 0xC18, 0);
    struct CollisionScaleAndFlags { float scale[7]; u32 packed; } collisionData;
    static_assert(sizeof(CollisionScaleAndFlags) == 0x20, "Collision payload layout changed!");
    const float reciprocal = 1.0f / baseScale;
    for (int i = 0; i < 7; ++i) {
        collisionData.scale[i] = reciprocal *
            soValueAccesser::getConstantFloat(moduleAccesser, 0xC19 + i, 0);
    }
    // Native stores (modelResult << 23) | (priorWord & 0x1FFFF) | 0x90000
    // at stack +0x44. No initialization of priorWord is visible in this TU.
    // HYPOTHESIS: use zero for those preserved low bits until a caller/frame
    // source establishes a deterministic value; never read indeterminate C++.
    collisionData.packed = (static_cast<u32>(modelResult) << 23) | 0x90000;

    soCollisionHitModule& hit = moduleAccesser->getCollisionHitModule();
    typedef void (*HitSetup)(soCollisionHitModule*, int, CollisionScaleAndFlags*, int);
    ((HitSetup)(*(u32**)(&hit))[0x38 / 4])(&hit, 0, &collisionData, 0);
    typedef void (*TwoInts)(void*, int, int);
    ((TwoInts)(*(u32**)(&hit))[0x50 / 4])(&hit, 3, 0);
    typedef void (*ThreeInts)(void*, int, int, int);
    ((ThreeInts)(*(u32**)(&hit))[0x44 / 4])(&hit, 0, 0, 0);

    soVisibilityModule& visibility = moduleAccesser->getVisibilityModule();
    visibility.setWhole(0);
    soMotionModule& motion = moduleAccesser->getMotionModule();
    soMotionChangeParam change(0x1B9, 0.0f, 1.0f, 0, 0, 0, 0);
    typedef void (*MotionParam)(soMotionModule*, soMotionChangeParam*);
    ((MotionParam)(*(u32**)(&motion))[0x80 / 4])(&motion, &change);

    // Native invokes the capture module at +0x40 slots +0x54 and +0x30.
    typedef void (*SlotInt)(void*, int);
    void* capture = *(void**)((u8*)moduleAccesser->m_enumerationStart + 0x40);
    ((SlotInt)(*(u32**)capture)[0x54 / 4])(capture, 0);
    ((TwoInts)(*(u32**)capture)[0x30 / 4])(capture, 0, 0);
}

void ftStatusUniqProcessYoshiEgg::execStatus(soModuleAccesser* moduleAccesser) {
    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    soMotionModule& motion = moduleAccesser->getMotionModule();
    soControllerModule& controller = moduleAccesser->getControllerModule();

    // Native loads D67 into f1 before motion vslot +0xBC. The method identity
    // is still unresolved, but its float argument is explicit in the call ABI.
    const float motionArg = soValueAccesser::getConstantFloat(moduleAccesser, 0xD67, 0);
    typedef void (*MotionFloat)(soMotionModule*, float);
    ((MotionFloat)(*(u32**)(&motion))[0xBC / 4])(&motion, motionArg);
    const float threshold = soValueAccesser::getConstantFloat(moduleAccesser, 0xD6C, 0);
    const float remaining = workGetFloat(&work, WorkFloat08);
    const float now = controller.getClatterTime(0);
    const bool elapsedPastThreshold = (remaining - now) > threshold;
    workSetFloat(&work, now, WorkFloat08);

    if (now <= 0.0f) { // Ordered fcmpo + (LT|EQ): NaN continues below.
        moduleAccesser->getStatusModule().changeStatusRequest(0xE, moduleAccesser);
        return;
    }

    float launch = workGetFloat(&work, WorkFloat05);
    // Motion vslot +0x24 is setRate(float).
    if (launch > 0.0f && launch - 1.0f <= 0.0f && !elapsedPastThreshold) {
        motion.setRate(1.0f);
        launch = 0.0f;
    }
    if (launch <= 0.0f && elapsedPastThreshold) {
        motion.setRate(soValueAccesser::getConstantFloat(moduleAccesser, 0xD6E, 0));
        launch = soValueAccesser::getConstantFloat(moduleAccesser, 0xD6D, 0);
    }
    workSetFloat(&work, launch, WorkFloat05);
}

void ftStatusUniqProcessYoshiEgg::execFixPosCounter(soModuleAccesser* moduleAccesser) {
    soSituationModule& situation = moduleAccesser->getSituationModule();
    soGroundModule& ground = moduleAccesser->getGroundModule();
    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    soKineticModule& kinetic = moduleAccesser->getKineticModule();

    // Both situation slots and ground slot are left unnamed, but receivers and
    // raw arguments follow the native instruction stream exactly.
    typedef int (*SituationQuery)(soSituationModule*);
    const int changed = ((SituationQuery)(*(u32**)(&situation))[0x1C / 4])(&situation);
    if (changed != 0) {
        const int priorSituation = ((SituationQuery)(*(u32**)(&situation))[0x14 / 4])(&situation);
        typedef void (*GroundMode)(soGroundModule*, int, int);
        if (priorSituation == 0) {
            ((GroundMode)(*(u32**)(&ground))[0x54 / 4])(&ground, 1, 0);
            kinetic.changeKinetic(6, moduleAccesser);
        } else {
            ((GroundMode)(*(u32**)(&ground))[0x54 / 4])(&ground, 5, 0);
            kinetic.changeKinetic(0, moduleAccesser);
            ftKineticEnergyController& controller =
                dynamic_cast<ftKineticEnergyController&>(*kinetic.getEnergy(2));
            controller.m_accelMul = workGetFloat(&work, WorkFloat04);
        }
    }

    if (workIsFlag(&work, WorkFlag10)) {
        return;
    }
    const float remaining = workGetFloat(&work, WorkFloat06);
    if (remaining <= 0.0f) {
        workOnFlag(&work, WorkFlag10);
        return;
    }

    const float start = soValueAccesser::getConstantFloat(moduleAccesser, 0xD69, 0);
    const float end = soValueAccesser::getConstantFloat(moduleAccesser, 0xD68, 0);
    const float phase = ((start - (remaining - 1.0f)) / start) * end;
    const float base = workGetFloat(&work, WorkFloat07);
    const float c18 = soValueAccesser::getConstantFloat(moduleAccesser, 0xC18, 0);
    soPostureModule& posture = moduleAccesser->getPostureModule();
    typedef void (*PostureFloat)(soPostureModule*, float);
    ((PostureFloat)(*(u32**)(&posture))[0x64 / 4])(&posture,
        ((1.0f - end) + phase) * (base * c18));
    workSetFloat(&work, remaining - 1.0f, WorkFloat06);
}

void ftStatusUniqProcessYoshiEgg::exitStatus(soModuleAccesser* moduleAccesser, int nextStatusKind) {
    if (nextStatusKind == 0xE) {
        soKineticModule& kinetic = moduleAccesser->getKineticModule();
        ftKineticEnergyController& controller =
            dynamic_cast<ftKineticEnergyController&>(*kinetic.getEnergy(2));
        ftKineticEnergyGravity& gravity =
            dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
        soSituationModule& situation = moduleAccesser->getSituationModule();
        typedef void (*SituationSet)(soSituationModule*, int, int);
        ((SituationSet)(*(u32**)(&situation))[0x20 / 4])(&situation, 2, 0);
        soGroundModule& ground = moduleAccesser->getGroundModule();
        typedef void (*GroundMode)(soGroundModule*, int, int);
        ((GroundMode)(*(u32**)(&ground))[0x54 / 4])(&ground, 5, 0);

        controller.m_speed.m_x = soValueAccesser::getConstantFloat(moduleAccesser, 0xD6F, 0);
        controller.m_speed.m_y = 0.0f;
        gravity.m_speedY = soValueAccesser::getConstantFloat(moduleAccesser, 0xD70, 0);
        ((u8*)&gravity)[5] |= 0x80;
        const int hitParam = soValueAccesser::getConstantInt(moduleAccesser, 0x5A53, 0);
        soCollisionHitModule& hit = moduleAccesser->getCollisionHitModule();
        typedef void (*HitInt)(soCollisionHitModule*, int, int);
        ((HitInt)(*(u32**)(&hit))[0x74 / 4])(&hit, hitParam, 0);
    }

    const float postureOffset = workGetFloat(&moduleAccesser->getWorkManageModule(), WorkFloat07);
    soPostureModule& posture = moduleAccesser->getPostureModule();
    typedef void (*PostureFloat)(soPostureModule*, float);
    ((PostureFloat)(*(u32**)(&posture))[0x64 / 4])(&posture, postureOffset);
    soCollisionHitModule& hit = moduleAccesser->getCollisionHitModule();
    void* hitParam = soValueAccesser::getConstantIndefinite(moduleAccesser, 0xA803, 0);
    typedef void (*HitParam)(soCollisionHitModule*, void*, int);
    ((HitParam)(*(u32**)(&hit))[0x3C / 4])(&hit, hitParam, 0);

    soVisibilityModule& visibility = moduleAccesser->getVisibilityModule();
    ((void (*)(soVisibilityModule*, int))(*(u32**)(&visibility))[0x24 / 4])(&visibility, 1);
    soLinkModule& link = moduleAccesser->getLinkModule();
    struct UnlinkData { int unk00; u8 unk04; } unlink = { 0x20, 0 };
    typedef void (*LinkCall)(soLinkModule*, int, UnlinkData*, int);
    ((LinkCall)(*(u32**)(&link))[0x48 / 4])(&link, -1, &unlink, 0);

    if (nextStatusKind == 0xEF) {
        const int roll = randi(5);
        const int motionKind = roll == 1 ? 0xA5 : roll == 2 ? 0xA6 : roll == 3 ? 0xA7 :
                               roll == 4 ? 0xA8 : 0xA4;
        soMotionChangeParam motionParam(motionKind, 0.0f, 1.0f, 0, 0, 0, 0);
        soMotionModule& motion = moduleAccesser->getMotionModule();
        typedef void (*MotionParam)(soMotionModule*, soMotionChangeParam*);
        ((MotionParam)(*(u32**)(&motion))[0x80 / 4])(&motion, &motionParam);
    }
}

bool ftStatusUniqProcessYoshiEgg::checkDamage(soModuleAccesser* moduleAccesser, void* param) {
    u8* bytes = (u8*)param;
    const int taskId = *(int*)(bytes + 0x1C);
    if (taskId != -1 && bytes[0x32] == 10) {
        gfTask* task = gfTask::getTask(taskId);
        if (task != 0) {
            // Native r7=1: reference cast, with no post-cast null check.
            StageObject& object = dynamic_cast<StageObject&>(*task);
            if (object.soGetSubKind() == 9 &&
                soExternalValueAccesser::getStatusKind(&object) == 0x116) {
                return false;
            }
        }
    }
    const float multiplier = soValueAccesser::getConstantFloat(moduleAccesser, 0xD71, 0);
    const float input = *(float*)(bytes + 4);
    soControllerModule& controller = moduleAccesser->getControllerModule();
    controller.addClatterTime(-(input * multiplier), 0);
    return true;
}