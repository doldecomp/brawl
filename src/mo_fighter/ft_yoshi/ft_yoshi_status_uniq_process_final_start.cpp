#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/yoshi/ft_yoshi_final_param.h>
#include <ft/ft_common_data_accesser.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>

void ftYoshiStatusUniqProcessFinalStart::initStatus(soModuleAccesser* acc) {
    ftData* data = g_ftCommonDataAccesser.getData(Fighter_Yoshi);
    ftYoshiFinalParam* param = static_cast<ftYoshiFinalParam*>(data->extendParam[3]);

    // HYPOTHESIS: this work float is the initial Super Dragon flight speed.
    // The native formula is 60 * extension-param[3].unk5C minus its unk60
    // field multiplied by constant 0xDB2.
    float initialSpeed = 60.0f * param->unk5C;
    initialSpeed -= param->unk60 * soValueAccesser::getConstantFloat(acc, 0xDB2, 0);
    acc->getWorkManageModule().setFloat(initialSpeed, 0x21000004);
}

ftYoshiStatusUniqProcessFinalStart g_ftYoshiStatusUniqProcessFinalStart;