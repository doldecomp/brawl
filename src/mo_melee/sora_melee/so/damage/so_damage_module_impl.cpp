#include <so/damage/so_damage_module_impl.h>
#include <so/so_module_accesser.h>
#include <gf/gf_task_scheduler.h>
#include <so/so_external_value_accesser.h>
#include <so/stageobject.h>
#include <types.h>

#include <mt/mt_vector.h>
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
};

extern soLogEventPresenter g_soLogEventPresenter;

soDamageModule::~soDamageModule() { }

soDamageModuleImpl::~soDamageModuleImpl() { }

// MATCH-ONLY: the original reads the attack data bitfields as whole words (lwz) with unsigned extraction.
static inline u32 getAttackDataWord(soCollisionAttackData* attackData, int offset) {
    return *(u32*)((u8*)attackData + offset);
}

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

soDamageTransactor* soDamageModuleImpl::getTransactor() {
    return m_transactor;
}

bool soDamageModuleImpl::onGroundDamage() {
    return false;
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

float soDamageModuleImpl::getReactionMul(soCollisionAttackData* attackData, u32 damageIndex, u8 hitIndex) {
    return 1.0f;
}

float soDamageModuleImpl::getReactionSub(soCollisionAttackData* attackData, u32 damageIndex, u8 hitIndex) {
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
        m_effector->reqCommonEffect(tmp, kb, m_moduleAccesser, attackData, collisionLog);
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
