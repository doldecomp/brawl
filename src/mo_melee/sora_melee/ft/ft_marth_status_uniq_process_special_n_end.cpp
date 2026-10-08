#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/marth/ft_marth_status_uniq_process.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>
#include <types.h>

ftMarthStatusUniqProcessSpecialNEnd g_ftMarthStatusUniqProcessSpecialNEnd;
void ftMarthStatusUniqProcessSpecialNEnd::initStatus(soModuleAccesser*) { }
void ftMarthStatusUniqProcessSpecialNEnd::execFixPos(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    int power = acc->getConstantIntKirby(24001) +
                (work.getInt(0x20000000) / 30) * acc->getConstantIntKirby(24002);
    // Each complete thirty-frame charge step raises every active hitbox's power.
    for (int i = 0; i < (s32)acc->getCollisionAttackModule().getPartSize(); i++) {
        if (acc->getCollisionAttackModule().isAttack(i, false)) {
            acc->getCollisionAttackModule().setPower(i, power, false);
        }
    }
}
void ftMarthStatusUniqProcessSpecialNEnd::exitStatus(soModuleAccesser*, int) { }
