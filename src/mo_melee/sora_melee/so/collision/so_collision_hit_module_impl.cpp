#include <so/collision/so_collision_hit_module_impl.h>
#include <so/collision/so_collision_attack_module_impl.h>
#include <so/so_module_accesser.h>
#include <types.h>

void soCollisionHitModuleImpl::event2nd(soCollisionAttackModule* attackModule, soModuleAccesser* attackerAccesser, soCollisionLog* collisionLog, u32 groupIndex) {
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
    if (!(*(u32*)((u8*)statusData + 0xc) >> 31)) {
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
