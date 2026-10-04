#include <so/damage/so_damage_transactor_actor.h>
#include <so/damage/so_damage_util_actor.h>
#include <so/damage/so_damage_effector_impl.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <nw4r/math/math_arithmetic.h>
#include <types.h>

// MATCH-ONLY: the original reads the attack data bitfields as whole words (lwz) with unsigned extraction.
static inline u32 getAttackDataWord(soDamage* damage, int offset) {
    return *(u32*)((u8*)&damage->m_attackData + offset);
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

bool soDamageTransactorActor::onDamageSub(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog, bool* isNotFlinch) {
    float reaction = damage->m_reaction;
    *isNotFlinch = true;
    if (0.0f == reaction && damage->m_powerMax <= 0.0f) {
        return false;
    }
    if (((getAttackDataWord(damage, 0x38) >> 5) & 1) == 1) {
        if (isSpeedDamage(moduleAccesser) == 1) {
            setupSpeedDamage(moduleAccesser, damage, damageLog);
        }
        return false;
    }
    switch (getAttackDataWord(damage, 0x30) & 0x1f) {
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

void soDamageTransactorActor::onFlowerDamage(soModuleAccesser* moduleAccesser, soDamage* damage) {
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

void soDamageTransactorActor::setupDamageStatusNormal(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog, int unk) {
    float speedMul;
    float newLr;
    Vec2f groundNormal;
    Vec2f dir;
    Vec2f speed;
    int situationKind = moduleAccesser->getSituationModule().getKind();
    int statusKind = getDamageStatusKind(moduleAccesser);
    float lr = moduleAccesser->getPostureModule().getLr();
    u32 attribute = getAttackDataWord(damage, 0x30) & 0x1f;
    int forcedStatus = 0;
    bool isDamageAir = true;
    bool isGround = false;
    int situation = moduleAccesser->getSituationModule().getKind();
    float reaction = damage->m_reaction;
    float frameReaction = reaction * soValueAccesser::getConstantFloat(moduleAccesser, 2002, 0);
    int level = soDamageUtilActor::getDamageLevel(moduleAccesser, frameReaction);
    Vec2f attackSpeed;
    Vec2f::copy(attackSpeed, damage->m_speed);
    float angle = soDamageUtilActor::getDamageAngle(moduleAccesser, reaction, damage->m_lr, damage->m_attackData.m_vector, &attackSpeed);
    bool isMeteor = soDamageUtilActor::checkDamageMeteor(moduleAccesser, damage->m_attackData.m_vector);
    float damageLr = damage->m_lr;
    newLr = damageLr;
    speedMul = reaction * soValueAccesser::getConstantFloat(moduleAccesser, 2010, 0);
    int height = getDamageHeight(moduleAccesser, damage->m_collisionLog.m_damageIndex);
    if (statusKind == 15) {
        forcedStatus = 15;
    }
    switch (attribute) {
    case soCollisionAttackData::Attribute_Ice:
        if (statusKind != 15 && level >= 2) {
            forcedStatus = 15;
            float halfPi = 1.5707964f;
            dir.m_x = (float)cos(angle) + (float)cos(halfPi);
            dir.m_y = (float)sin(angle) + (float)sin(halfPi);
            if (dir.m_x * dir.m_x + dir.m_y * dir.m_y <= 0.0001f) {
                angle = 0.0f;
            } else {
                angle = atan2(dir.m_y, dir.m_x);
            }
        }
        break;
    case soCollisionAttackData::Attribute_Lay:
        if (forcedStatus == 0) {
            forcedStatus = 21;
        }
        break;
    case soCollisionAttackData::Attribute_Bury:
        if (forcedStatus == 0 && situation == 0) {
            forcedStatus = 6;
        }
        break;
    case soCollisionAttackData::Attribute_Pitfall:
        if (forcedStatus == 0 && situation == 0) {
            if (moduleAccesser->getGroundModule().isPassableGround(0)) {
                forcedStatus = 20;
            } else {
                forcedStatus = 6;
                attribute = 11;
            }
        }
        break;
    case soCollisionAttackData::Attribute_Slip:
        if (forcedStatus == 0 && situation == 0) {
            if (0.0f == damage->m_powerMax) {
                forcedStatus = 9;
            } else {
                forcedStatus = 10;
            }
        }
        break;
    case soCollisionAttackData::Attribute_Sleep:
        if (forcedStatus == 0 && situation == 0) {
            forcedStatus = 11;
        }
        break;
    case soCollisionAttackData::Attribute_Stun:
        if (forcedStatus == 0 && situation == 0) {
            forcedStatus = 14;
        }
        break;
    }
    if (forcedStatus != 0) {
        level = 2;
    }
    if (damage->m_attackData.m_vector == 365) {
        speed.m_x = damage->m_speed.m_x;
        speed.m_y = damage->m_speed.m_y;
    } else {
        speed.m_x = -damageLr * (speedMul * (float)cos(angle));
        speed.m_y = speedMul * (float)sin(angle);
    }
    if (situation == 0) {
        Vec2f normal = moduleAccesser->getGroundModule().getTouchNormal(8, 0);
        isGround = true;
        float groundAngle;
        float lenProduct = (normal.m_x * normal.m_x + normal.m_y * normal.m_y) * (speed.m_x * speed.m_x + speed.m_y * speed.m_y);
        groundNormal.m_x = normal.m_x;
        groundNormal.m_y = normal.m_y;
        if (0.0f == lenProduct) {
            groundAngle = 0.0f;
        } else {
            float dot = normal.m_x * speed.m_x + normal.m_y * speed.m_y;
            float c = dot * rsqrtf(lenProduct);
            const float hi = 1.0f;
            const float lo = -1.0f;
            float clamped = nw4r::math::FSelect(c - lo, c, lo);
            clamped = nw4r::math::FSelect(clamped - hi, hi, clamped);
            groundAngle = acos(clamped);
        }
        if (0.0f == angle && level > 2) {
            level = 2;
        }
        if (groundAngle < 1.5707964f) {
            if (level == 3) {
                statusKind = 4;
            } else {
                statusKind = 7;
            }
        } else if (level == 3) {
            statusKind = 4;
            if (groundAngle > 1.5707964f + soValueAccesser::getConstantFloat(moduleAccesser, 2013, 0)) {
                speed.m_y *= -soValueAccesser::getConstantFloat(moduleAccesser, 2014, 0);
                moduleAccesser->getDamageModule().getEffector()->reqDamageGroundBeatDownEffect(moduleAccesser, &groundNormal);
            }
        } else {
            statusKind = 8;
            isDamageAir = false;
            if (forcedStatus == 0) {
                forcedStatus = checkDownDamage(reaction, angle, moduleAccesser);
                if (forcedStatus != 0) {
                    newLr = lr;
                }
            } else if (forcedStatus == 15) {
                forcedStatus = 15;
            }
            if (forcedStatus == 0) {
                if (reaction >= soValueAccesser::getConstantFloat(moduleAccesser, 2032, 0) || damage->m_attackData.m_slipChance != 0.0f) {
                    if (isSlip(moduleAccesser, damage->m_attackData.m_slipChance)) {
                        statusKind = 10;
                    }
                }
            }
        }
    } else {
        if (level == 3) {
            statusKind = 4;
        } else {
            statusKind = 7;
        }
    }
    if (forcedStatus != 0) {
        statusKind = forcedStatus;
    }
    if (statusKind == 4) {
        statusKind = soDamageUtilActor::getDamageFlyStatus(moduleAccesser, damage->m_damage, angle);
    }
    int hitStopFrame = soDamageUtilActor::getDamageHitStopFrame(moduleAccesser, damage, false, 1.0f);
    float hitStopMul = getHitStopMul(moduleAccesser);
    if (1.0f != hitStopMul) {
        hitStopFrame = (int)((float)hitStopFrame * hitStopMul);
    }
    if (situation == 2 && damage->m_attackData.m_vector != 365) {
        if (onCompositionDamageSpeed(moduleAccesser, damage, &speed, level) == 1) {
            statusKind = 0;
        }
    }
    bool doHitStop = false;
    if (hitStopFrame > 0) {
        if (attribute == 3 || attribute == 20) {
            if (statusKind == 3 || statusKind == 0) {
                if (statusKind != 9) {
                    doHitStop = true;
                }
            }
        } else if (statusKind != 9) {
            doHitStop = true;
        }
    }
    if (statusKind == 11) {
        if (isSleepStatus(moduleAccesser) == 1) {
            return;
        }
    }
    if (attribute == 20) {
        if (isParalyzeDamage(moduleAccesser) == 1) {
            return;
        }
    }
    if (attribute == 12) {
        if (isBindStatus(moduleAccesser) == 1) {
            return;
        }
    }
    if (attribute == 11) {
        if (isBuryStatus(moduleAccesser) == 1) {
            return;
        }
    }
    if (doHitStop == true) {
        moduleAccesser->getStopModule().setHitStopFrame(hitStopFrame, true);
    }
    damageLog->m_reaction = reaction;
    damageLog->m_level = (soDamage::Level)level;
    damageLog->m_height = height;
    damageLog->m_speed.m_x = speed.m_x;
    damageLog->m_speed.m_y = speed.m_y;
    damageLog->m_angle = angle;
    damageLog->m_lr = damageLr;
    damageLog->m_frame = frameReaction;
    damageLog->m_hitStopFrame = hitStopFrame;
    damageLog->m_attribute = (soCollisionAttackData::Attribute)(getAttackDataWord(damage, 0x30) & 0x1f);
    damageLog->m_damageAdd = damage->m_damageAdd;
    damageLog->m_attackerTeamNo = damage->m_collisionLog.m_teamNo;
    damageLog->m_hitStopDelay = damage->m_attackData.m_hitStopDelay;
    Vec2f groundNormalCopy;
    Vec2f::copy(groundNormalCopy, groundNormal);
    damageLog->m_groundTouchNormal.m_x = groundNormalCopy.m_x;
    damageLog->m_groundTouchNormal.m_y = groundNormalCopy.m_y;
    damageLog->m_attackerTaskId = damage->m_collisionLog.m_taskId;
    damageLog->m_attackerTeamOwnerId = damage->m_attackerTeamOwnerId;
    *((u8*)damageLog + 0x44) = *((u8*)damage + 0x32); // MATCH-ONLY: byte copy of the task category bitfield
    damageLog->m_isSituationGround = isGround;
    damageLog->m_isDamageAir = isDamageAir;
    damageLog->m_unk26 = false;
    damageLog->m_isCollisionAbsolute = damage->m_collisionLog.m_isAbsolute;
    damageLog->m_isMeteor = isMeteor;
    damageLog->m_isAttackDirect = (getAttackDataWord(damage, 0x38) >> 13) & 1;
    damageLog->m_isVector365 = damage->m_attackData.m_vector == 365;
    if (statusKind != 0) {
        if (statusKind == 11) {
            addSleepTime(moduleAccesser, damage, damageLog);
        }
        if (isUseTurn(moduleAccesser) == 1) {
            moduleAccesser->getPostureModule().setLr(newLr);
        }
        onDamageChangeStatusRequest(statusKind, moduleAccesser, damageLog);
    }
    moduleAccesser->getSituationModule().getKind();
    if ((u32)damage->m_collisionLog.m_taskId != 0xFFFFFFFF) {
        checkCheer(reaction, angle, moduleAccesser, damageLog);
    }
    moduleAccesser->getDamageModule().getEffector()->reqUniqEffect(moduleAccesser, level, &damage->m_attackData);
    moduleAccesser->getDamageModule().getEffector()->reqDamageEffectParam(damage->m_damageAdd, reaction, moduleAccesser, &damage->m_attackData);
    if (attribute == 20) {
        onParalyzeDamage(moduleAccesser, damage, damageLog);
    }
    moduleAccesser->getDamageModule().getEffector()->reqQuake(frameReaction, moduleAccesser, level);
    if (damage->m_reaction > 0.0f && hitStopFrame > 0) {
        moduleAccesser->getDamageModule().getEffector()->reqShake(moduleAccesser, situationKind, &groundNormal, &damage->m_attackData, hitStopFrame);
    }
}

bool soDamageTransactorActor::isSlip(soModuleAccesser* moduleAccesser, float slipChance) {
    return false;
}

float soDamageTransactorActor::getHitStopMul(soModuleAccesser* moduleAccesser) {
    return 1.0f;
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

void soDamageTransactorActor::addSleepTime(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) {
}

void soDamageTransactorActor::checkCheer(float reaction, float angle, soModuleAccesser* moduleAccesser, soDamageLog* damageLog) {
}

void soDamageTransactorActor::onParalyzeDamage(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) {
}

void soDamageTransactorActor::setupDamageStatusTurn(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) {
    int situationKind = moduleAccesser->getSituationModule().getKind();
    const soModuleEnumeration* modules = moduleAccesser->m_enumerationStart;
    soTurnModuleLocal* turnModule = (soTurnModuleLocal*)modules->m_turnModule;
    float lr = modules->m_postureModule->getLr();
    turnModule->startTurn(lr, soValueAccesser::getConstantIndefinite(moduleAccesser, 0xA411, 0), true, true);
    moduleAccesser->getStopModule().setOtherStop(turnModule->getTurnFrame());
    Vec2f speed;
    Vec2f attackSpeed;
    Vec2f::copy(attackSpeed, damage->m_speed);
    float angle = soDamageUtilActor::getDamageAngle(moduleAccesser, damage->m_reaction, damage->m_lr, damage->m_attackData.m_vector, &attackSpeed);
    speed.m_x = damage->m_lr * (float)cos(angle);
    speed.m_y = sin(angle);
    if (situationKind == 0) {
        speed = speed * soValueAccesser::getConstantFloat(moduleAccesser, 2024, 0);
    } else {
        speed = speed * soValueAccesser::getConstantFloat(moduleAccesser, 2023, 0);
    }
    u32 attribute = getAttackDataWord(damage, 0x30) & 0x1f;
    damageLog->m_speed = speed;
    damageLog->m_angle = angle;
    damageLog->m_attribute = (soCollisionAttackData::Attribute)attribute;
    Vec3f speed3(speed.m_x, speed.m_y, 0.0f);
    moduleAccesser->getKineticModule().addSpeedOutside(soKineticEnergy::Outside_Attack, &speed3);
    moduleAccesser->getDamageModule().toTurnDamage();
}

void soDamageTransactorActor::setupSpeedDamage(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) {
    Vec2f speed;
    Vec2f attackSpeed;
    Vec2f::copy(attackSpeed, damage->m_speed);
    float angle = soDamageUtilActor::getDamageAngle(moduleAccesser, damage->m_reaction, damage->m_lr, damage->m_attackData.m_vector, &attackSpeed);
    speed.m_x = -damage->m_lr * (float)cos(angle);
    speed.m_y = sin(angle);
    float mul = damage->m_reaction * soValueAccesser::getConstantFloat(moduleAccesser, 2010, 0);
    soKineticEnergy::AttributeFlag attr(soKineticEnergy::ATTRIBUTE_MASK_DAMAGE);
    speed.m_x *= mul;
    speed.m_y *= mul;
    Vec2f sum;
    sum = moduleAccesser->getKineticModule().getSumSpeed(attr);
    if (sum.m_x * speed.m_x + sum.m_y * speed.m_y >= 0.0f) {
        speed = speed - sum;
    }
    Vec3f speed3(speed.m_x, speed.m_y, 0.0f);
    moduleAccesser->getKineticModule().addSpeedOutside(soKineticEnergy::Outside_Attack, &speed3);
}

void soDamageTransactorActor::setupDamageStatusNoReaction(soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) {
    float frameMul = soValueAccesser::getConstantFloat(moduleAccesser, 2002, 0);
    int level = soDamageUtilActor::getDamageLevel(moduleAccesser, damage->m_reaction * frameMul);
    moduleAccesser->getDamageModule().getEffector()->reqUniqEffect(moduleAccesser, level, &damage->m_attackData);
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

int soDamageTransactorActor::checkDownDamage(float reaction, float angle, soModuleAccesser* moduleAccesser) {
    soDamageTransactor* transactor = moduleAccesser->getDamageModule().getTransactor();
    int kind = transactor->getDamageStatusKind(moduleAccesser);
    int ret = 0;
    switch (kind) {
    case 1:
    case 2:
    case 3:
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
        break;
    }
    return ret;
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
