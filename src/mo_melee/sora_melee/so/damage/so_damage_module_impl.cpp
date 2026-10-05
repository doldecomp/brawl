#include <so/damage/so_damage_module_impl.h>
#include <so/so_module_accesser.h>
#include <gf/gf_task_scheduler.h>
#include <so/so_external_value_accesser.h>
#include <so/stageobject.h>
#include <types.h>

#include <mt/mt_vector.h>
#include <nw4r/math/math_arithmetic.h>
#include <so/collision/so_collision_attack_module_impl.h>
#include <so/model/so_model_module_simple.h>

// HYPOTHESIS: field names of the unnamed parts follow the header; _160 is two floats' worth of unknown data.

// HYPOTHESIS: reconstructed interfaces of two modules that are untyped (void*) in the headers;

// only the slots called here are known.
class soDebugModuleLocal {
public:
    virtual void unk08();
    virtual void unk0c();
    virtual void unk10();
    virtual void unk14();
    virtual bool isDamageDisabled();
};

class soCaptureModuleLocal {
public:
    virtual void unk08();
    virtual void unk0c();
    virtual void unk10();
    virtual void unk14();
    virtual void unk18();
    virtual void unk1c();
    virtual int getCaptureTaskId();
};

// HYPOTHESIS: statistic/log singleton at bss 0x2cbc; method name taken from the map (soLogEventPresenter::notifyLogEventCollisionHit)
class soLogEventPresenter {
public:
    void notifyLogEventCollisionHit(float damage, int attackerTaskId, int defenderId, int unk);
    void notifyLogEventGroundDamage(float damage, StageObject* stageObject);
};

extern soLogEventPresenter g_soLogEventPresenter;

soDamageModule::~soDamageModule() { }

soDamageModuleImpl::~soDamageModuleImpl() { }

// MATCH-ONLY: the original reads the attack data bitfields as whole words (lwz) with unsigned extraction.
static inline u32 getAttackDataWord(soCollisionAttackData* attackData, int offset) {
    return *(u32*)((u8*)attackData + offset);
}

// HYPOTHESIS: reconstructed interface of the glow module (untyped in the headers); only two slots are known.
class soGlowModuleLocal : public soNullable {
public:
    virtual void unk0c();
    virtual void unk10();
    virtual void unk14();
    virtual void unk18();
    virtual void unk1c();
    virtual bool isPowerBoostActive();
    virtual void unk24();
    virtual void unk28();
    virtual void unk2c();
    virtual void unk30();
    virtual void unk34();
    virtual void unk38();
    virtual void unk3c();
    virtual void unk40();
    virtual void unk44();
    virtual void unk48();
    virtual void unk4c();
    virtual void unk50();
    virtual void unk54();
    virtual void unk58();
    virtual void unk5c();
    virtual void unk60();
    virtual void unk64();
    virtual void unk68();
    virtual void unk6c();
    virtual float modifyPower(float power, soCollisionAttackData* attackData, void* attackerGlowModule);
};

// HYPOTHESIS: reconstructed interface of the abnormal module (untyped in the headers).
class soAbnormalModuleLocal : public soNull, public soNullable {
public:
    virtual void unk0();
    virtual void unk1();
    virtual void unk2();
    virtual void unk3();
    virtual float getReactionMul();
};

// MATCH-ONLY: byte table (indexed by attack attribute) kept in .rodata right after the float pool
// (tells whether the weight based reaction multiplier applies for the attribute).
static const u8 s_attributeUsesWeight[24] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
    1, 1, 1, 1, 0, 1, 0, 0,
};

// Angle between two 2D vectors in radians (acos of the clamped normalized dot product).
// HYPOTHESIS: inline helper in the original (the same code appears in soDamageTransactorActor).
static inline float vec2Angle(const Vec2f& a, const Vec2f& b) {
    float angle;
    float lengthProduct = (b.m_x * b.m_x + b.m_y * b.m_y) * (a.m_x * a.m_x + a.m_y * a.m_y);
    if (0.0f == lengthProduct) {
        angle = 0.0f;
    } else {
        float dot = a.m_x * b.m_x + a.m_y * b.m_y;
        float c = dot * rsqrtf(lengthProduct);
        float clamped = nw4r::math::FSelect(c - -1.0f, c, -1.0f);
        clamped = nw4r::math::FSelect(clamped - 1.0f, 1.0f, clamped);
        angle = acos(clamped);
    }
    return angle;
}

void soDamageModuleImpl::activate(float damage) {
    initDamage(damage);
    m_isDamageLock = false;
    m_damageMul = 1.0f;
    m_reactionMul = 1.0f;
    m_reactionMul2nd = 1.0f;
    m_noReactionModule.reset();
    initInfo();
    m_attackerInfo.clear();
}

void soDamageModuleImpl::update() {
    m_attackerInfo.update();
}

void soDamageModuleImpl::initDamage(float damage) {
    int size = m_damageArray->size();
    for (int i = 0; i < size; i++) {
        soDamage& d = m_damageArray->at(i);
        d.m_damage = damage;
        d.m_damageAdd = 0.0f;
        d.m_damageAdd_ = 0.0f;
    }
}

void soDamageModuleImpl::initInfo() {
    if (m_sleep != 1) {
        int size = m_damageArray->size();
        for (int i = 0; i < size; i++) {
            soDamage& d = m_damageArray->at(i);
            d.m_reaction = 0.0f;
            d.m_powerMax = 0.0f;
            d.m_damageAdd = 0.0f;
            d.m_isFlinchFlag = false;
        }
    }
    *(int*)&_160[0] = -1;
}

void soDamageModuleImpl::clearAttackerInfo() {
    m_attackerInfo.clear();
}

void soDamageModuleImpl::setInfo() {
    u32 defenderTaskId;
    if (m_sleep != 1) {
        int size = m_damageArray->size();
        for (int i = 0; i < size; i++) {
            soDamage& d = m_damageArray->at(i);
            if (d.m_reaction > 0.0f || d.m_powerMax > 0.0f) {
                gfTask* task = gfTaskScheduler::getInstance()->getTaskById((gfTask::Category)*((u8*)&d + 0x32), *(u32*)((u8*)&d + 0x1c));
                defenderTaskId = m_moduleAccesser->m_stageObject->m_taskId;
                StageObject& attacker = dynamic_cast<StageObject&>(*task);
                soCollisionAttackModule* attackModule = soExternalValueAccesser::getCollisionAttackModule(&attacker);
                d.m_attackData = *attackModule->getData(d.m_collisionLog.m_collsionIndex, d.m_collisionLog.m_isAbsolute);
                d.m_pos = attackModule->getCenterPos(d.m_collisionLog.m_collsionIndex, d.m_collisionLog.m_isAbsolute);
                d.m_speed = attackModule->getSpeed();
                if ((u32)attackModule->getIndirectTaskId() != 0xFFFFFFFF) {
                    gfTask* indirectTask = gfTaskScheduler::getInstance()->getTask((u32)attackModule->getIndirectTaskId());
                    if (indirectTask != NULL) {
                        m_attackerInfo.setIndirect(defenderTaskId, &attacker, &dynamic_cast<StageObject&>(*indirectTask));
                        *(int*)&_160[0] = attackModule->getIndirectTaskId();
                        *(int*)&_160[4] = attackModule->getIndirectTeamNo();
                        m_moduleAccesser->getCollisionAttackModule().setIndirectInfo(*(int*)&_160[0], *(int*)&_160[4]);
                        d.m_attackerTeamOwnerId = soExternalValueAccesser::getTeamOwnerId(&dynamic_cast<StageObject&>(*indirectTask));
                        return;
                    }
                    m_attackerInfo.set(defenderTaskId, &attacker);
                } else {
                    m_attackerInfo.set(defenderTaskId, &attacker);
                }
                d.m_attackerTeamOwnerId = soExternalValueAccesser::getTeamOwnerId(&attacker);
            }
        }
    }
}

void soDamageEventObserver::notifyEventOnDamage(soDamage* damage, bool unk, soModuleAccesser* moduleAccesser) {
}

void soDamageEventObserver::notifyEventAddDamage(soDamage* damage, soModuleAccesser* moduleAccesser) {
}

bool soDamageModuleImpl::isCheckGroundDamage() {
    return false;
}

bool soDamageModuleImpl::setGroundDamage(u32 touchKind, soCollisionAttackData* attackData) {
    bool damaged = false;
    soDamage* damage = &m_damageArray->at(0);
    float power = (float)attackData->m_power;
    if (attackData->m_vector == 361) {
        Vec2f normal = m_moduleAccesser->getGroundModule().getTouchNormal(touchKind, 0);
        Vec2f base(1.0f, 0.0f);
        float angle = vec2Angle(normal, base);
        attackData->m_vector = (int)(57.29578f * angle);
    }
    if (reinterpret_cast<soGlowModuleLocal*>(m_moduleAccesser->m_enumerationStart->m_glowModule)->isPowerBoostActive() == 1) {
        soGlowModuleLocal* glow = reinterpret_cast<soGlowModuleLocal*>(m_moduleAccesser->m_enumerationStart->m_glowModule);
        power = glow->modifyPower(power, attackData, (void*)8);
    }
    if (reinterpret_cast<soDebugModuleLocal*>(m_moduleAccesser->m_enumerationStart->m_debugModule)->isDamageDisabled() != 1) {
        soDamage& d = m_damageArray->at(0);
        d.m_damageAdd = d.m_damageAdd + power;
    }
    float damageAdd = damage->m_damageAdd;
    if (m_isDamageLock == 0) {
        damage->m_damage = damage->m_damage + damageAdd;
    }
    damage->m_powerMax = power;
    float kb = getTransactor()->getDamageForReaction(damage->m_damage, m_moduleAccesser);
    float weightMul;
    if (s_attributeUsesWeight[getAttackDataWord(attackData, 0x30) & 0x1f]) {
        weightMul = getWeightReactionMul(attackData);
    } else {
        weightMul = 1.0f;
    }
    if (attackData->m_reactionFix != 0) {
        kb = (float)attackData->m_reactionAdd
            + (18.0f + weightMul * (1.4f * (m_reactionMul * (1.0f + 0.05f * (10.0f * (float)attackData->m_reactionFix)))))
            * (0.01f * (float)attackData->m_reactionEffect);
    } else {
        float damageTerm = 0.1f * kb + 0.05f * (kb * power);
        kb = (float)attackData->m_reactionAdd
            + (18.0f + weightMul * (1.4f * (m_reactionMul * damageTerm)))
            * (0.01f * (float)attackData->m_reactionEffect);
    }
    float abnormalMul = reinterpret_cast<soAbnormalModuleLocal*>(m_moduleAccesser->m_enumerationStart->m_abnormalModule)->getReactionMul();
    kb *= (m_reactionMul2nd * getReactionMul(attackData, 0, -1)) * 1.0f * abnormalMul;
    kb -= getReactionSub(attackData, 0, -1);
    if (kb < 0.0f) {
        kb = 0.0f;
    } else if (kb > 2500.0f) {
        kb = 2500.0f;
    }
    damage->m_reaction = kb;
    damage->m_attackData = *attackData;
    Vec2f touchPos = m_moduleAccesser->getGroundModule().getTouchPos(touchKind, 0);
    damage->m_pos = Vec3f(touchPos.m_x, touchPos.m_y, 0.0f);
    damage->m_speed.m_x = 0.0f;
    damage->m_speed.m_y = 0.0f;
    if (touchKind == 2) {
        damage->m_lr = -1.0f;
    } else if (touchKind == 4) {
        damage->m_lr = 1.0f;
    } else {
        damage->m_lr = m_moduleAccesser->getPostureModule().getLr();
    }
    if (damageAdd > 0.0f || damage->m_reaction > 0.0f) {
        soCollisionLog log;
        // HYPOTHESIS: a fake collision log (no attacker task) is stored with the ground damage
        *(int*)&log._spacer[8] = 0;
        log.m_taskId = -1;
        log.m_pos = Vec3f(damage->m_pos.m_x, damage->m_pos.m_y, damage->m_pos.m_z);
        log.m_life = 0;
        log.m_30 = 0;
        log.m_teamNo = -1;
        log._33 = 0;
        *((u8*)&log + 0x22) = 0;
        log._35 = 0;
        log.m_collsionIndex = 0;
        log.m_damageIndex = 0;
        log._38 = 0;
        log.m_isAbsolute = false;
        log._40 = 0;
        log._41 = 0;
        log._42 = 0;
        damage->m_collisionLog = log;
        damaged = onGroundDamage();
        m_moduleAccesser->getSoundModule().playHitSE(damage->m_powerMax, &damage->m_attackData);
        if (((getAttackDataWord(attackData, 0x38) >> 6) & 1) == 0) {
            m_effector->reqCommonEffect(damage->m_powerMax, damage->m_reaction, damage->m_lr, m_moduleAccesser, attackData, &damage->m_collisionLog);
        }
        if (m_isDamageLock == 0) {
            soInstanceManagerFullProperty<soDamageEventObserver*>* observerList = soEventPresenter<soDamageEventObserver>::getObserverList();
            int count = observerList->size();
            for (int i = 0; i < count; i++) {
                observerList->atIndex(i)->notifyEventOnDamage(damage, damaged, m_moduleAccesser);
            }
        }
    }
    g_soLogEventPresenter.notifyLogEventGroundDamage(power, m_moduleAccesser->m_stageObject);
    return damaged;
}

soDamageTransactor* soDamageModuleImpl::getTransactor() {
    return m_transactor;
}

bool soDamageModuleImpl::onGroundDamage() {
    return false;
}

bool soDamageModuleImpl::setForceDamage(StageObject* stageObject, Vec3f* pos, u32 collisionIndex, u32 damageIndex, bool getAbsolute, bool initInfo) {
    bool damaged = false;
    u32 defenderTaskId = m_moduleAccesser->m_stageObject->m_taskId;
    soDamage* damage = &m_damageArray->at(damageIndex);
    soCollisionAttackModule* attackModule = soExternalValueAccesser::getCollisionAttackModule(stageObject);
    soCollisionAttackData* attackData = attackModule->getData(collisionIndex, getAbsolute);
    float power = (float)attackData->m_power;
    if (reinterpret_cast<soGlowModuleLocal*>(m_moduleAccesser->m_enumerationStart->m_glowModule)->isPowerBoostActive() == 1) {
        soGlowModuleLocal* glow = reinterpret_cast<soGlowModuleLocal*>(m_moduleAccesser->m_enumerationStart->m_glowModule);
        power = glow->modifyPower(power, attackData, soExternalValueAccesser::getGlowModule(stageObject));
    }
    if (reinterpret_cast<soDebugModuleLocal*>(m_moduleAccesser->m_enumerationStart->m_debugModule)->isDamageDisabled() != 1) {
        soDamage& d = m_damageArray->at(damageIndex);
        d.m_damageAdd = d.m_damageAdd + power;
    }
    float damageAdd = damage->m_damageAdd;
    if (m_isDamageLock == 0) {
        damage->m_damage = damage->m_damage + damageAdd;
    }
    damage->m_powerMax = power;
    float reactionMul = attackModule->getReactionMul(collisionIndex);
    float kb = getTransactor()->getDamageForReaction(damage->m_damage, m_moduleAccesser);
    float weightMul;
    if (s_attributeUsesWeight[getAttackDataWord(attackData, 0x30) & 0x1f]) {
        weightMul = getWeightReactionMul(attackData);
    } else {
        weightMul = 1.0f;
    }
    if (attackData->m_reactionFix != 0) {
        kb = (float)attackData->m_reactionAdd
            + (18.0f + weightMul * (1.4f * (m_reactionMul * (1.0f + 0.05f * (10.0f * (float)attackData->m_reactionFix)))))
            * (0.01f * (float)attackData->m_reactionEffect);
    } else {
        float damageTerm = 0.1f * kb + 0.05f * (kb * power);
        kb = (float)attackData->m_reactionAdd
            + (18.0f + weightMul * (1.4f * (m_reactionMul * damageTerm)))
            * (0.01f * (float)attackData->m_reactionEffect);
    }
    float abnormalMul = reinterpret_cast<soAbnormalModuleLocal*>(m_moduleAccesser->m_enumerationStart->m_abnormalModule)->getReactionMul();
    kb *= reactionMul * (m_reactionMul2nd * getReactionMul(attackData, damageIndex, -1)) * abnormalMul;
    kb -= getReactionSub(attackData, damageIndex, -1);
    if (kb < 0.0f) {
        kb = 0.0f;
    } else if (kb > 2500.0f) {
        kb = 2500.0f;
    }
    damage->m_reaction = kb;
    damage->m_attackData = *attackData;
    damage->m_pos = *pos;
    damage->m_speed.m_x = 0.0f;
    damage->m_speed.m_y = 0.0f;
    soPostureModule& posture = m_moduleAccesser->getPostureModule();
    float lr = posture.getLr();
    Vec3f postureCenter = posture.getPos();
    damage->m_lr = getDamageLr(postureCenter.m_x, lr, attackModule, attackData, collisionIndex, getAbsolute);
    if (damageAdd > 0.0f || damage->m_reaction > 0.0f) {
        soCollisionLog log;
        // HYPOTHESIS: a fake collision log describing the forcing object is stored with the damage
        *(int*)&log._spacer[8] = 0;
        log.m_taskId = stageObject->m_taskId;
        log.m_pos = Vec3f(damage->m_pos.m_x, damage->m_pos.m_y, damage->m_pos.m_z);
        log.m_life = 0;
        log.m_30 = 0;
        log.m_teamNo = -1;
        log._33 = 0;
        log.m_taskCategory = (gfTask::Category)stageObject->m_taskCategory;
        log._35 = 0;
        log.m_collsionIndex = collisionIndex;
        log.m_damageIndex = damageIndex;
        log._38 = 0;
        log.m_isAbsolute = getAbsolute;
        log._40 = 0;
        log._41 = 0;
        log._42 = 0;
        damage->m_collisionLog = log;
        damage->m_attackerTeamOwnerId = soExternalValueAccesser::getTeamOwnerId(stageObject);
        m_attackerInfo.set(defenderTaskId, stageObject);
        damaged = onDamage(damageIndex);
        m_moduleAccesser->getSoundModule().playHitSE(damage->m_powerMax, &damage->m_attackData);
        if (((getAttackDataWord(attackData, 0x38) >> 6) & 1) == 0) {
            m_effector->reqCommonEffect(damage->m_powerMax, damage->m_reaction, damage->m_lr, m_moduleAccesser, attackData, &damage->m_collisionLog);
        }
        if (m_isDamageLock == 0) {
            soInstanceManagerFullProperty<soDamageEventObserver*>* observerList = soEventPresenter<soDamageEventObserver>::getObserverList();
            int count = observerList->size();
            for (int i = 0; i < count; i++) {
                observerList->atIndex(i)->notifyEventOnDamage(damage, damaged, m_moduleAccesser);
            }
        }
    }
    if (initInfo) {
        this->initInfo();
    }
    return damaged;
}

bool soDamageModuleImpl::setForceDamage(StageObject* stageObject, int nodeId, u32 collisionIndex, u32 damageIndex, bool getAbsolute, bool initInfo) {
    int correctNodeId = m_moduleAccesser->getModelModule().getCorrectNodeId(nodeId);
    Vec3f pos = m_moduleAccesser->getModelModule().getNodeGlobalPosition(correctNodeId, false);
    return setForceDamage(stageObject, &pos, collisionIndex, damageIndex, getAbsolute, initInfo);
}

bool soDamageModuleImpl::setForceDamage(StageObject* stageObject, const char* nodeName, u32 collisionIndex, u32 damageIndex, bool getAbsolute, bool initInfo) {
    return setForceDamage(stageObject, m_moduleAccesser->getModelModule().getNodeId(nodeName), collisionIndex, damageIndex, getAbsolute, initInfo);
}

bool soDamageModuleImpl::onDamage(u32 damageIndex) {
    soDamage& damage = m_damageArray->at(damageIndex);
    soDamageLog log;
    bool result = getTransactor()->onDamage(m_moduleAccesser, &damage, &log);
    log.m_unk26 = false;
    return result;
}

void soDamageModuleImpl::storeDamage(float addedDamage, soDamage* damage) {
    float newDamage = damage->m_damage + addedDamage;
    if (newDamage > 999.0f) {
        newDamage = 999.0f;
    }
    damage->m_damage = newDamage;
}

void soDamageModuleImpl::addDamage(float addDamage, u32 damageIndex) {
    if (reinterpret_cast<soDebugModuleLocal*>(m_moduleAccesser->m_enumerationStart->m_debugModule)->isDamageDisabled() != 1) {
        soDamage& d = m_damageArray->at(damageIndex);
        d.m_damageAdd_ = d.m_damageAdd_ + addDamage;
    }
}

void soDamageModuleImpl::toTurnDamage() {
    m_noReactionModule.setMode(1);
}

void soDamageModuleImpl::leaveTurnDamage() {
    m_noReactionModule.setMode(0);
}

soDamageLog* soDamageModuleImpl::getDamageLog() {
    return 0;
}

float soDamageModuleImpl::getWeightReactionMul(soCollisionAttackData* attackData) {
    return 1.0f;
}

float soDamageModuleImpl::getReactionMul(soCollisionAttackData* attackData, u32 damageIndex, int hitIndex) {
    return 1.0f;
}

float soDamageModuleImpl::getReactionSub(soCollisionAttackData* attackData, u32 damageIndex, int hitIndex) {
    return 0.0f;
}

bool soDamageModuleImpl::isReaction() {
    int size = m_damageArray->size();
    for (int i = 0; i < size; i++) {
        if (m_damageArray->at(i).m_reaction > 0.0f) {
            return true;
        }
    }
    return false;
}

void soDamageModuleImpl::notifyEventCollisionHit(float power, soCollisionAttackData* attackData, u32 index, int unk, soModuleAccesser* moduleAccesser, soCollisionLog* collisionLog) {
    u8 unk29 = *((u8*)collisionLog + 0x29);
    if (unk29 != 1) {
        float damage = power * m_damageMul * getDamageMul();
        g_soLogEventPresenter.notifyLogEventCollisionHit(damage, collisionLog->m_taskId, moduleAccesser->m_stageObject->m_taskId, 0);
        if (reinterpret_cast<soDebugModuleLocal*>(m_moduleAccesser->m_enumerationStart->m_debugModule)->isDamageDisabled() != 1) {
            soDamage& d = m_damageArray->at(index);
            d.m_damageAdd = d.m_damageAdd + damage;
        }
        if (damage > m_damageArray->at(index).m_powerMax) {
            m_damageArray->at(index).m_powerMax = damage;
        }
        if (collisionLog->m_isAbsolute == 1) {
            if ((u32)collisionLog->m_taskId == reinterpret_cast<soCaptureModuleLocal*>(m_moduleAccesser->m_enumerationStart->m_captureModule)->getCaptureTaskId()) {
                m_damageArray->at(index).m_isFlinchFlag = true;
            }
        }
    }
}

float soDamageModuleImpl::getDamageMul() {
    return 1.0f;
}

float soDamageModuleImpl::getDamageLr(float posX, float lr, void* attackModulePtr, void* attackDataPtr, int index, int isAbsolute) {
    soCollisionAttackModule* attackModule = (soCollisionAttackModule*)attackModulePtr;
    soCollisionAttackData* attackData = (soCollisionAttackData*)attackDataPtr;
    switch (((*(u32*)((u8*)attackData + 0x38)) >> 10) & 7) { // MATCH-ONLY: unsigned extraction of the lrCheck bitfield
    case 1:
        {
            float speed = attackModule->getSpeedX();
            if (0.0f != speed) {
                if (speed > 0.0f) {
                    return -1.0f;
                }
                return 1.0f;
            }
        }
        // fallthrough
    case 0:
        if (posX > attackModule->getPosX(index, isAbsolute)) {
            return -1.0f;
        }
        return 1.0f;
    case 2:
        return lr;
    case 3:
        return -attackModule->getLr();
    case 4:
        return attackModule->getLr();
    case 5:
        {
            Vec3f center = attackModule->getCenterPos(index, isAbsolute);
            if (posX > center.m_x) {
                return -1.0f;
            }
            return 1.0f;
        }
    default:
        return 0.0f;
    }
}

bool soDamageModuleImpl::checkNoReaction(void* damagePtr) {
    soDamage* damage = (soDamage*)damagePtr;
    if (m_noReactionModule.checkNoReaction(damage->m_reaction, damage->m_powerMax, damage->m_collisionLog.m_isAbsolute) == 1) {
        if (getTransactor()->checkNoReaction(m_moduleAccesser, damage) == 1) {
            return true;
        }
    }
    return false;
}

void soDamageModuleImpl::heal(float healAmount, u32 damageIndex) {
    float current = getDamage(damageIndex);
    if (current + healAmount < 0.0f) {
        healAmount = -current;
    }
    if (healAmount + (current + m_damageArray->at(damageIndex).m_damageAdd_) < 0.0f) {
        healAmount = -current - m_damageArray->at(damageIndex).m_damageAdd_;
    }
    addDamage(healAmount, damageIndex);
}

float soDamageModuleImpl::getDamage(u32 damageIndex) {
    return m_damageArray->at(damageIndex).m_damage;
}

void soDamageModuleImpl::notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser) {
    m_isDamageLock = false;
    m_damageMul = 1.0f;
    m_reactionMul = 1.0f;
    m_reactionMul2nd = 1.0f;
    m_noReactionModule.resetModeStatus();
}

void soDamageModuleImpl::notifyEventCollisionHit2nd(float posX, float collisionLr, soCollisionAttackModule* attackModule, soCollisionLog* collisionLog, u32 groupIndex, soModuleAccesser* moduleAccesser, bool unk) {
    u8 damageIndex;
    u8 collisionIndex = collisionLog->m_collsionIndex;
    soCollisionAttackData* attackData = attackModule->getData(collisionIndex, collisionLog->m_isAbsolute);
    if (unk == 1) {
        if (((getAttackDataWord(attackData, 0x38) >> 6) & 1) == 0) {
            m_effector->reqInvincibleEffect(m_moduleAccesser, collisionLog);
        }
        return;
    }
    if (*((u8*)collisionLog + 0x29) == 1) {
        m_effector->reqTipEffect(m_moduleAccesser, collisionLog);
        return;
    }
    soDamage* damage = &m_damageArray->at(groupIndex);
    float reactionMul = attackModule->getReactionMul(collisionIndex);
    damageIndex = collisionLog->m_damageIndex;
    float kb = getTransactor()->getDamageForReaction(damage->m_damage + damage->m_damageAdd, m_moduleAccesser);
    float tmp = attackModule->getBasePower(collisionIndex, collisionLog->m_isAbsolute);
    float weightMul;
    if (s_attributeUsesWeight[getAttackDataWord(attackData, 0x30) & 0x1f]) {
        weightMul = getWeightReactionMul(attackData);
    } else {
        weightMul = 1.0f;
    }
    if (attackData->m_reactionFix != 0) {
        kb = (float)attackData->m_reactionAdd
            + (18.0f + weightMul * (1.4f * (m_reactionMul * (1.0f + 0.05f * (10.0f * (float)attackData->m_reactionFix)))))
            * (0.01f * (float)attackData->m_reactionEffect);
    } else {
        float damageTerm = 0.1f * kb + 0.05f * (kb * tmp);
        kb = (float)attackData->m_reactionAdd
            + (18.0f + weightMul * (1.4f * (m_reactionMul * damageTerm)))
            * (0.01f * (float)attackData->m_reactionEffect);
    }
    tmp = reinterpret_cast<soAbnormalModuleLocal*>(m_moduleAccesser->m_enumerationStart->m_abnormalModule)->getReactionMul();
    kb *= reactionMul * (m_reactionMul2nd * getReactionMul(attackData, groupIndex, damageIndex)) * tmp;
    kb -= getReactionSub(attackData, groupIndex, damageIndex);
    if (kb < 0.0f) {
        kb = 0.0f;
    } else if (kb > 2500.0f) {
        kb = 2500.0f;
    }
    tmp = attackModule->getPower(collisionIndex, collisionLog->m_isAbsolute);
    float lr = getDamageLr(posX, collisionLr, attackModule, attackData, collisionIndex, collisionLog->m_isAbsolute);
    if (kb > damage->m_reaction) {
        damage->m_collisionLog = *collisionLog;
        damage->m_reaction = kb;
        damage->m_lr = lr;
    }
    if (0.0f == damage->m_reaction && damage->m_powerMax > 0.0f) {
        damage->m_collisionLog = *collisionLog;
        damage->m_reaction = kb;
        damage->m_lr = lr;
    }
    if (((getAttackDataWord(attackData, 0x38) >> 6) & 1) == 0) {
        m_effector->reqCommonEffect(tmp, kb, lr, m_moduleAccesser, attackData, collisionLog);
    }
}

bool soDamageModuleImpl::isObserv(char unk1) {
    return unk1 == 0x1e;
}

void soDamageModuleImpl::setDamageLock(bool lock) {
    m_isDamageLock = lock;
}

bool soDamageModuleImpl::isDamageLock() {
    return m_isDamageLock;
}

void soDamageModuleImpl::setReactionMul2nd(float reactionMul2nd) {
    m_reactionMul2nd = reactionMul2nd;
}

void soDamageModuleImpl::setReactionMul(float reactionMul) {
    m_reactionMul = reactionMul;
}

void soDamageModuleImpl::setDamageMul(float damageMul) {
    m_damageMul = damageMul;
}

bool soDamageModuleImpl::isCaptureCut() {
    return false;
}

bool soDamageModuleImpl::isCaptureCut(void* unk) {
    *(u8*)unk = 0;
    return false;
}

float soDamageModuleImpl::getCaptureDamage() {
    return 0.0f;
}

bool soDamageModuleImpl::isCatchCut() {
    return false;
}

soDamageEffector* soDamageModuleImpl::getEffector() {
    return m_effector;
}

void soDamageModuleImpl::restoreAttackerInfo(soDamageAttackerInfo* attackerInfo) {
    m_attackerInfo.copy(attackerInfo);
}

void soDamageModuleImpl::getAttackerInfo(soDamageAttackerInfo* attackerInfo) {
    attackerInfo->copy(&m_attackerInfo);
}

soDamageAttackerInfo* soDamageModuleImpl::getAttackerInfo() {
    return &m_attackerInfo;
}

bool soDamageModuleImpl::isNoReactionModePerfect() {
    return m_noReactionModule.m_isModePerfect;
}

void soDamageModuleImpl::setNoReactionModePerfect(bool perfect) {
    m_noReactionModule.m_isModePerfect = perfect;
}

void soDamageModuleImpl::setNoReactionModeAlways(bool always) {
    m_noReactionModule.m_isModeAlways = always;
}

void soDamageModuleImpl::resetNoReactionMode() {
    m_noReactionModule.resetMode();
}

void soDamageModuleImpl::setNoReactionMode(int mode) {
    m_noReactionModule.setMode(mode);
}

void soDamageModuleImpl::resetNoReactionModeStatus() {
    m_noReactionModule.resetModeStatus();
}

void soDamageModuleImpl::setNoReactionMode2nd(float unk1, float unk2, int mode) {
    m_noReactionModule.set(unk1, unk2, true, mode);
}

void soDamageModuleImpl::setNoReactionModeStatus(float unk1, float unk2, int mode) {
    m_noReactionModule.set(unk1, unk2, false, mode);
}

float soDamageModuleImpl::getPowerMax(u32 damageIndex) {
    return m_damageArray->at(damageIndex).m_powerMax;
}

void soDamageModuleImpl::sleep(bool sleep) {
    m_sleep = sleep;
}

void soDamageModuleImpl::deactivate() {
}

void soDamageModuleImpl::clearDamageLog() {
}

void soDamageModuleImpl::reqDamageEffect() {
}

float soDamageModuleImpl::getReaction(u32 damageIndex) {
    return m_damageArray->at(damageIndex).m_reaction;
}

void soDamageModuleImpl::updateAttackerInfo() {
}

bool soDamageModuleImpl::preProcessCheckDamage() {
    return false;
}

void soDamageModuleImpl::reqDamageShake() {
}
