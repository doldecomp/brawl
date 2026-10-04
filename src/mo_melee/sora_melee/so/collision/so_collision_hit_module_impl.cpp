#include <so/collision/so_collision_hit_module_impl.h>
#include <so/collision/so_collision_attack_module_impl.h>
#include <so/so_module_accesser.h>
#include <gf/gf_task_scheduler.h>
#include <nw4r/ut/ut_list.h>
#include <so/so_external_value_accesser.h>
#include <so/stageobject.h>
#include <types.h>

// HYPOTHESIS: partial view of soStatusData (the real definition is empty in the headers)
struct soStatusDataView {
    char _0[0xc];
    u32 : 24;
    u32 m_keepHit : 1;
};

void soCollisionHitModuleImpl::event2nd(soCollisionAttackModule* attackModule, void* attackerGlowModule, soCollisionLog* collisionLog, u32 groupIndex) {
    bool flag = true;
    if (attackModule->isInvalidInvincible(collisionLog->m_collsionIndex, collisionLog->m_isAbsolute) != 0 || getTotalStatus(0) != 1) {
        flag = false;
    }
    soInstanceManagerFullProperty<soCollisionHitEventObserver*>* observerList = soEventPresenter<soCollisionHitEventObserver>::getObserverList();
    for (int i = 0; i < observerList->size(); i++) {
        float lr = m_collisionHitGroupArray->at(groupIndex).m_lr;
        soCollisionHitEventObserver* observer = observerList->atIndex(i);
        float posX = m_collision.getPosX(groupIndex);
        observer->notifyEventCollisionHit2nd(posX, lr, attackModule, collisionLog, groupIndex, m_moduleAccesser, flag);
    }
}

void soCollisionHitModuleImpl::checkLog() {
    typedef void (soCollisionHitModuleImpl::*HitEventFunc)(soCollisionAttackModule*, void*, soCollisionLog*, u32);
    static const HitEventFunc eventFuncs[2] = { &soCollisionHitModuleImpl::event, &soCollisionHitModuleImpl::event2nd };
    int groupNum = m_collisionHitGroupArray->size();
    for (u32 funcIndex = 0; funcIndex < 2; funcIndex++) {
        HitEventFunc func = eventFuncs[funcIndex];
        for (int groupIndex = 0; groupIndex < groupNum; groupIndex++) {
            nw4r::ut::List* logList = (nw4r::ut::List*)m_collision.getLogList(groupIndex);
            soCollisionLog* log = NULL;
            while ((log = (soCollisionLog*)nw4r::ut::List_GetNext(logList, log)) != NULL) {
                if (*((u8*)log + 0x21) == 0) {
                    gfTask* task = gfTaskScheduler::getInstance()->getTaskById((gfTask::Category)*((u8*)log + 0x22), log->m_taskId);
                    if (task != NULL) {
                        StageObject& stageObject = dynamic_cast<StageObject&>(*task);
                        soCollisionAttackModule* attackModule = soExternalValueAccesser::getCollisionAttackModule(&stageObject);
                        if (attackModule->isInvalidXlu(log->m_collsionIndex, log->m_isAbsolute) || getTotalStatus(0) != 2) {
                            void* attackerGlowModule = soExternalValueAccesser::getGlowModule(&stageObject);
                            (this->*func)(attackModule, attackerGlowModule, log, groupIndex);
                        }
                    }
                }
            }
        }
    }
}

u32 soCollisionHitModuleImpl::getGroupNum() {
    return m_collisionHitGroupArray->size();
}

void soCollisionHitModuleImpl::setPosX(float posX, u32 collisionGroupIndex) {
    m_collision.setPosX(posX, collisionGroupIndex);
}

float soCollisionHitModuleImpl::getPosX(u32 collisionGroupIndex) {
    return m_collision.getPosX(collisionGroupIndex);
}

Vec3f soCollisionHitModuleImpl::getCenterPos(u16 index, u32 collisionHitGroupIndex) {
    return m_collisionHitGroupArray->at(collisionHitGroupIndex).getCenterPos(&m_collision, index);
}

bool soCollisionHitModuleImpl::isObserv(char unk1) {
    return unk1 == 6;
}

void soCollisionHitModuleImpl::notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser) {
    // HYPOTHESIS: bit 31 of the word at +0xc of the status data keeps the hit state across the status change
    if (!((soStatusDataView*)statusData)->m_keepHit) {
        resetStatusAll(0);
        setWhole(0, 0);
        setNoTeam(false);
    }
}

void soCollisionHitModuleImpl::renderDebug() {
}

void soCollisionHitModuleImpl::setReactionFrame(short reactionFrame) {
    m_reactionFrame = reactionFrame;
}

short soCollisionHitModuleImpl::getReactionFrame() {
    return m_reactionFrame;
}

bool soCollisionHitModuleImpl::isReactionFrame() {
    return m_reactionFrame >= 0;
}
