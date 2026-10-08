#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/purin/ft_purin_status_uniq_process.h>
#include <gm/gm_global.h>
#include <so/so_module_accesser.h>

void ftPurinStatusUniqProcessSpecialHi::initStatus(soModuleAccesser* moduleAccesser) {
    if (g_GameGlobal->m_modeMelee->m_meleeInitData.m_isAmplifySongAttack) {
        moduleAccesser->getWorkManageModule().onFlag(0x22000011);
    }
    moduleAccesser->getWorkManageModule().onFlag(0x22000012);
}

void ftPurinStatusUniqProcessSpecialHi::execStatus(soModuleAccesser*) { }

void ftPurinStatusUniqProcessSpecialHi::execFixPos(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000012)) {
        moduleAccesser->getWorkManageModule().offFlag(0x22000012);
    }
    // The amplified-song setting waits for attack zero to exist before
    // changing its whole-attack property, then consumes the request.
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000011) &&
        moduleAccesser->getCollisionAttackModule().isAttack(0, false)) {
        moduleAccesser->getCollisionAttackModule().setWhole(0, true);
        moduleAccesser->getWorkManageModule().offFlag(0x22000011);
    }
}


void ftPurinStatusUniqProcessSpecialHi::exitStatus(soModuleAccesser*, int) { }

ftPurinStatusUniqProcessSpecialHi g_ftPurinStatusUniqProcessSpecialHi;
