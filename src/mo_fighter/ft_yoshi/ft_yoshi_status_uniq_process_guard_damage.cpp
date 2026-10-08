#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/yoshi/ft_yoshi.h>
#include <so/so_module_accesser.h>
void ftYoshiStatusUniqProcessGuardDamage::exitStatus(soModuleAccesser* acc, int nextStatus) {
    ftStatusUniqProcessGuardDamage::exitStatus(acc, nextStatus);
    if (nextStatus != Fighter::Status::Guard_On && nextStatus != Fighter::Status::Guard && nextStatus != Fighter::Status::Guard_Damage && nextStatus != Fighter::Status::Escape_F && nextStatus != Fighter::Status::Escape_B) {
        dynamic_cast<ftYoshi&>(acc->getStageObject()).deleteGuardColorAnim();
    }
}
ftYoshiStatusUniqProcessGuardDamage g_ftYoshiStatusUniqProcessGuardDamage(ftYoshiStatusUniqProcessGuardFunc::getInstance());
