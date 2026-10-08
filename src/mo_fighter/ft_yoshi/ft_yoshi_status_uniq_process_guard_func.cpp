#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/yoshi/ft_yoshi.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
void ftYoshiStatusUniqProcessGuardFunc::updateShield(soModuleAccesser* acc) {
    setShieldScale(acc);
}
void ftYoshiStatusUniqProcessGuardFunc::setShieldScale(soModuleAccesser* acc) {
    float scale = soValueAccesser::getConstantFloat(acc, 0xbe6, 0);
    Vec3f nodeScale(scale, scale, scale);
    soModelModule& model = acc->getModelModule();
    model.setNodeScale(model.getCorrectNodeId(0x12c), &nodeScale);
    dynamic_cast<ftYoshi&>(acc->getStageObject()).updateGuardColorAnim();
}
ftYoshiStatusUniqProcessGuardFunc g_ftYoshiStatusUniqProcessGuardFunc;
