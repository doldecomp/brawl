#include <ft/ft_status_uniq_process_guard.h>
#include <types.h>

ftStatusUniqProcessGuard g_ftStatusUniqProcessGuard;

void ftStatusUniqProcessGuard::initStatus(soModuleAccesser* moduleAccesser) {
    moduleAccesser->getCollisionShieldModule().setStatus(0, 1, 0);
}

void ftStatusUniqProcessGuard::execStatus(soModuleAccesser* moduleAccesser) {
    ftStatusUniqProcessGuardOn::execStatus(moduleAccesser);
}

void ftStatusUniqProcessGuard::exitStatus(soModuleAccesser* moduleAccesser, int) {
    moduleAccesser->getCollisionShieldModule().setStatus(0, 0, 0);
}
