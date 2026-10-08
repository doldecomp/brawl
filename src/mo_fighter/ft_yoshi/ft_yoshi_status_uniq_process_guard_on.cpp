#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/yoshi/ft_yoshi.h>
#include <so/so_module_accesser.h>

void ftYoshiStatusUniqProcessGuardOn::initStatus(soModuleAccesser* acc) {
    ftStatusUniqProcessGuardOn::initStatus(acc);
    dynamic_cast<ftYoshi&>(acc->getStageObject()).createGuardColorAnim();
}
void ftYoshiStatusUniqProcessGuardOn::exitStatus(soModuleAccesser* acc, int nextStatus) {
    ftStatusUniqProcessGuardOn::exitStatus(acc, nextStatus);
    // Retain the egg shield's color animation throughout the guard family.
    if (nextStatus != Fighter::Status::Guard_On && nextStatus != Fighter::Status::Guard &&
        nextStatus != Fighter::Status::Guard_Damage && nextStatus != Fighter::Status::Escape_F &&
        nextStatus != Fighter::Status::Escape_B) {
        dynamic_cast<ftYoshi&>(acc->getStageObject()).deleteGuardColorAnim();
    }
}
ftYoshiStatusUniqProcessGuardOn g_ftYoshiStatusUniqProcessGuardOn(ftYoshiStatusUniqProcessGuardFunc::getInstance());
