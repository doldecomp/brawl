#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/marth/ft_marth_status_uniq_process.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>
#include <types.h>

ftMarthStatusUniqProcessSpecialNLoop g_ftMarthStatusUniqProcessSpecialNLoop;
void ftMarthStatusUniqProcessSpecialNLoop::initStatus(soModuleAccesser* acc) {
    soWorkManageModule& work = acc->getWorkManageModule();
    work.setInt(acc->getConstantIntKirby(24000) * 30, 0x20000001);
}
void ftMarthStatusUniqProcessSpecialNLoop::exitStatus(soModuleAccesser*, int) { }
