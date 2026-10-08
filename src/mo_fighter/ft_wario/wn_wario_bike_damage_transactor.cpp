#include <wn/wario/wn_wario_bike_damage_transactor.h>
#include <wn/wario/wn_wario_bike_link_event.h>
#include <so/so_module_accesser.h>
#include <so/kinetic/so_kinetic_module_impl.h>
#include <so/stop/so_stop_module_impl.h>

// HYPOTHESIS: event 0x843 is the bike's no-reaction notification; its numeric
// kind and payload layout are observed, but the gameplay label is not.
struct WarioBikeNoReactionDamageEvent : soLinkEventArgs {
    int hitStopFrame;
    bool unk0C;

    WarioBikeNoReactionDamageEvent(int frame)
        : soLinkEventArgs(0x843), hitStopFrame(frame), unk0C(true) {
    }
};
static_assert(sizeof(WarioBikeNoReactionDamageEvent) == 0x10, "Event payload layout changed");

wnWarioBikeDamageTransactorImpl::~wnWarioBikeDamageTransactorImpl() {
}

int wnWarioBikeDamageTransactorImpl::getDamageValueParam(soModuleAccesser*) { return 0; }
bool wnWarioBikeDamageTransactorImpl::onDamageChangeStatusRequest(int, soModuleAccesser*, soDamageLog*) { return true; }
int wnWarioBikeDamageTransactorImpl::getDamageStatusKind(soModuleAccesser*) { return 0; }
bool wnWarioBikeDamageTransactorImpl::isUseTurnDamage(soModuleAccesser*) { return true; }
bool wnWarioBikeDamageTransactorImpl::isUseTurn(soModuleAccesser*) { return true; }
bool wnWarioBikeDamageTransactorImpl::isApplyTurnDamage(soModuleAccesser*) { return true; }
int wnWarioBikeDamageTransactorImpl::getDamageHeight(soModuleAccesser*, u8) { return 0; }
float wnWarioBikeDamageTransactorImpl::getHitStopMul(soModuleAccesser*) { return 1.0f; }
bool wnWarioBikeDamageTransactorImpl::isSlip(soModuleAccesser*, float) { return false; }
bool wnWarioBikeDamageTransactorImpl::isSleepStatus(soModuleAccesser*) { return false; }
bool wnWarioBikeDamageTransactorImpl::isParalyzeDamage(soModuleAccesser*) { return false; }
void wnWarioBikeDamageTransactorImpl::addSleepTime(soModuleAccesser*, soDamage*, soDamageLog*) {}
void wnWarioBikeDamageTransactorImpl::onFlowerDamage(soModuleAccesser*, soDamage*) {}
void wnWarioBikeDamageTransactorImpl::onParalyzeDamage(soModuleAccesser*, soDamage*, soDamageLog*) {}
void wnWarioBikeDamageTransactorImpl::setFlagDownDamage3(soModuleAccesser*, bool) {}
bool wnWarioBikeDamageTransactorImpl::isCheckGroundDamage(soModuleAccesser*) { return false; }
void wnWarioBikeDamageTransactorImpl::onGroundDamageAfter(soModuleAccesser*) {}
bool wnWarioBikeDamageTransactorImpl::onCompositionDamageSpeed(soModuleAccesser*, soDamage*, Vec2f*, int) { return false; }
void wnWarioBikeDamageTransactorImpl::setupDamageStatusNormal(soModuleAccesser*, soDamage*, soDamageLog*, int) {}
void wnWarioBikeDamageTransactorImpl::setupDamageStatusTurn(
    soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) {
    soDamageTransactorActor::setupDamageStatusTurn(moduleAccesser, damage, damageLog);
    // HYPOTHESIS: 0x842 notifies the rider that the bike received turn damage.
    ftWarioBikeLinkEvent event(0x842);
    moduleAccesser->getLinkModule().sendEventParents(3, event);

    Vec3f reflection(-1.0f, 0.0f, 0.0f);
    soKineticEnergy::AttributeFlag damageAttribute(1);
    moduleAccesser->getKineticModule().reflectSpeed(&reflection, damageAttribute);
}
void wnWarioBikeDamageTransactorImpl::setupSpeedDamage(soModuleAccesser*, soDamage*, soDamageLog*) {}
void wnWarioBikeDamageTransactorImpl::setupDamageStatusNoReaction(
    soModuleAccesser* moduleAccesser, soDamage* damage, soDamageLog* damageLog) {
    soDamageTransactorActor::setupDamageStatusNoReaction(moduleAccesser, damage, damageLog);
    WarioBikeNoReactionDamageEvent event(moduleAccesser->getStopModule().getHitStopFrame());
    moduleAccesser->getLinkModule().sendEventParents(3, event);
}
void wnWarioBikeDamageTransactorImpl::setupDamageFlyRollStatus(float, float, soModuleAccesser*, soDamageLog*) {}
float wnWarioBikeDamageTransactorImpl::getReactionSub(soModuleAccesser*) { return 0.0f; }
float wnWarioBikeDamageTransactorImpl::getReactionMul(soModuleAccesser*) { return 1.0f; }
float wnWarioBikeDamageTransactorImpl::getDamageMul(soModuleAccesser*) { return 1.0f; }
void wnWarioBikeDamageTransactorImpl::checkCheer(float, float, soModuleAccesser*, soDamageLog*) {}
float wnWarioBikeDamageTransactorImpl::getDamageForReaction(float damage, soModuleAccesser*) { return damage; }

bool wnWarioBikeDamageTransactorImpl::isSpeedDamage(soModuleAccesser*) { return true; }

static wnWarioBikeDamageTransactorImpl s_warioBikeDamageTransactor;
