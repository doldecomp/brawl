#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <so/so_module_accesser.h>

// The grounded startup stays airborne until its animation work flag releases it.
void ftYoshiStatusUniqProcessSpecialLw::initStatus(soModuleAccesser* moduleAccesser) {
    moduleAccesser->getSituationModule().setKeepAir(true);
}

void ftYoshiStatusUniqProcessSpecialLw::execFixPos(soModuleAccesser* moduleAccesser) {
    // HYPOTHESIS: flag 0x22000010 marks the end of the forced-air startup.
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000010)) {
        moduleAccesser->getSituationModule().setKeepAir(false);
    }
}

ftYoshiStatusUniqProcessSpecialLw g_ftYoshiStatusUniqProcessSpecialLw;
