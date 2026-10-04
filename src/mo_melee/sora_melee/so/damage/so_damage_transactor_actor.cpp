#include <so/damage/so_damage_transactor_actor.h>
#include <so/damage/so_damage_util_actor.h>
#include <so/damage/so_damage_effector_impl.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

float soDamageTransactorActor::getHitStopMul(soModuleAccesser* moduleAccesser) {
    return 1.0f;
}

bool soDamageTransactorActor::isSlip(soModuleAccesser* moduleAccesser) {
    return false;
}

bool soDamageTransactorActor::onCompositionDamageSpeed(soModuleAccesser* moduleAccesser, soDamage* damage, Vec2f* speed, int level) {
    return false;
}

bool soDamageTransactorActor::isSleepStatus(soModuleAccesser* moduleAccesser) {
    return false;
}

bool soDamageTransactorActor::isParalyzeDamage(soModuleAccesser* moduleAccesser) {
    return false;
}

bool soDamageTransactorActor::isBindStatus(soModuleAccesser* moduleAccesser) {
    return false;
}

bool soDamageTransactorActor::isBuryStatus(soModuleAccesser* moduleAccesser) {
    return false;
}

void soDamageTransactorActor::addSleepTime(soModuleAccesser* moduleAccesser, soDamage* damage) {
}

void soDamageTransactorActor::checkCheer(soModuleAccesser* moduleAccesser, soDamage* damage) {
}

void soDamageTransactorActor::onParalyzeDamage(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) {
}

bool soDamageTransactorActor::checkNoReaction(soModuleAccesser* moduleAccesser) {
    return true;
}

void soDamageTransactorActor::getDamageForReaction(soModuleAccesser* moduleAccesser) {
}

float soDamageTransactorActor::getDamageMul(soModuleAccesser* moduleAccesser) {
    return 1.0f;
}

float soDamageTransactorActor::getReactionMul(soModuleAccesser* moduleAccesser) {
    return 1.0f;
}

float soDamageTransactorActor::getReactionSub(soModuleAccesser* moduleAccesser) {
    return 0.0f;
}

void soDamageTransactorActor::onGroundDamageAfter(soModuleAccesser* moduleAccesser) {
}

void soDamageTransactorActor::setFlagDownDamage3(soModuleAccesser* moduleAccesser, bool flag) {
}

bool soDamageTransactorActor::isCheckGroundDamage(soModuleAccesser* moduleAccesser) {
    return false;
}

void soDamageTransactorActor::onFlowerDamage(soModuleAccesser* moduleAccesser, soDamage* damage) {
}

// HYPOTHESIS: reconstructed interface of the turn module (only the slots called here are known)
class soTurnModuleLocal {
public:
    virtual void unk08();
    virtual void unk0c();
    virtual void startTurn(float lr, void* turnParam, bool unk1, bool unk2);
    virtual void unk14();
    virtual void unk18();
    virtual void unk1c();
    virtual void unk20();
    virtual void unk24();
    virtual void unk28();
    virtual u32 getTurnFrame();
};


int soDamageTransactorActor::checkDownDamage(float reaction, float angle, soModuleAccesser* moduleAccesser) {
    soDamageTransactor* transactor = moduleAccesser->getDamageModule().getTransactor();
    int ret = 0;
    int kind = transactor->getDamageStatusKind(moduleAccesser);
    if (kind < 4 && kind >= 1) {
        if (reaction >= soValueAccesser::getConstantFloat(moduleAccesser, 2025, 0)) {
            if (reaction >= soValueAccesser::getConstantFloat(moduleAccesser, 2026, 0)) {
                if (angle < 0.017453292f * soValueAccesser::getConstantFloat(moduleAccesser, 2027, 0)) {
                    transactor->setFlagDownDamage3(moduleAccesser, true);
                    ret = 3;
                }
            } else {
                transactor->setFlagDownDamage3(moduleAccesser, false);
                ret = 3;
            }
        }
    }
    return ret;
}
