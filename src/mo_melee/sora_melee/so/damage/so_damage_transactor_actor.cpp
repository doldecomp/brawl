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

bool soDamageTransactorActor::onDamageSub(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog, bool* isNotFlinch) {
    *isNotFlinch = true;
    if (damage->m_reaction == 0.0f && damage->m_powerMax <= 0.0f) {
        return false;
    }
    if (damage->m_attackData.m_noTransaction == 1) {
        if (isSpeedDamage(moduleAccesser) == 1) {
            setupSpeedDamage(moduleAccesser, damage, damageLog);
        }
        return false;
    }
    switch (damage->m_attackData.m_attribute) {
    case soCollisionAttackData::Attribute_Flower:
        onFlowerDamage(moduleAccesser, damage);
        break;
    case soCollisionAttackData::Attribute_Turn:
        if (isUseTurnDamage(moduleAccesser) == 1) {
            if (isApplyTurnDamage(moduleAccesser) == 1) {
                setupDamageStatusTurn(moduleAccesser, damage, damageLog);
                return true;
            }
        }
        break;
    }
    if (moduleAccesser->getDamageModule().checkNoReaction(damage) == 1) {
        setupDamageStatusNoReaction(moduleAccesser, damage, damageLog);
        return false;
    }
    *isNotFlinch = false;
    return false;
}

bool soDamageTransactorActor::onDamage(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) {
    bool isNotFlinch = false;
    if (onDamageSub(moduleAccesser, damage, damageLog, &isNotFlinch) == 0) {
        if (isNotFlinch == true && damage->m_isFlinchFlag == 0) {
            return false;
        }
        if (moduleAccesser->getStatusModule().checkDamage(moduleAccesser, damage) == 1) {
            setupDamageStatusNoReaction(moduleAccesser, damage, damageLog);
            return true;
        }
        setupDamageStatusNormal(moduleAccesser, damage, damageLog, -1);
    }
    return true;
}

void soDamageTransactorActor::setupDamageStatusNoReaction(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) {
    float frameMul = soValueAccesser::getConstantFloat(moduleAccesser, 2002, 0);
    int level = soDamageUtilActor::getDamageLevel(moduleAccesser, damage->m_reaction * frameMul);
    moduleAccesser->getDamageModule().getEffector()->reqCommonEffectParam(moduleAccesser, level, &damage->m_attackData);
    int hitStopFrame = soDamageUtilActor::getDamageHitStopFrame(moduleAccesser, damage, true, 1.0f);
    if (hitStopFrame > 0) {
        moduleAccesser->getStopModule().setHitStopFrame(hitStopFrame, true);
    }
}

void soDamageTransactorActor::setupDamageFlyRollStatus(float angle, float speed, soModuleAccesser* moduleAccesser, soDamageLog* damageLog) {
    Vec2f vec(speed, 0.0f);
    Vec2f rotated;
    vec.rot(&rotated, angle * 0.017453292f);
    float reaction = speed / soValueAccesser::getConstantFloat(moduleAccesser, 2010, 0);
    float frame = reaction * soValueAccesser::getConstantFloat(moduleAccesser, 2002, 0);
    damageLog->m_reaction = reaction;
    damageLog->m_level = soDamage::Level_FlyRoll;
    damageLog->m_height = -1;
    damageLog->m_speed.m_x = 0.0f;
    damageLog->m_speed.m_y = 0.0f;
    damageLog->m_angle = 0.0f;
    damageLog->m_lr = 1.0f;
    damageLog->m_frame = frame;
    damageLog->m_hitStopFrame = 0;
    damageLog->m_attribute = soCollisionAttackData::Attribute_Normal;
    damageLog->m_damageAdd = 0.0f;
    damageLog->m_attackerTeamNo = -1;
    damageLog->m_hitStopDelay = 1.0f;
    damageLog->m_attackerTaskId = -1;
    damageLog->m_isDamageAir = false;
    damageLog->m_unk26 = false;
    damageLog->m_isCollisionAbsolute = false;
    damageLog->m_isMeteor = false;
    damageLog->m_isAttackDirect = false;
    damageLog->m_isVector365 = false;
    damageLog->m_speed.m_x = rotated.m_x;
    damageLog->m_speed.m_y = rotated.m_y;
    onDamageChangeStatusRequest(5, moduleAccesser, damageLog);
}
