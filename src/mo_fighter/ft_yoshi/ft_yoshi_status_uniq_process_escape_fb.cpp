// MATCH-ONLY: keep the original shared Vec3f constructor calls out of line.
#pragma dont_inline on
#include <mt/mt_vector.h>
#pragma dont_inline reset
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/yoshi/ft_yoshi.h>
#include <so/so_module_accesser.h>
void ftYoshiStatusUniqProcessEscapeFB::exitStatus(soModuleAccesser* acc, int nextStatus) {
    if (nextStatus != Fighter::Status::Guard) {
        dynamic_cast<ftYoshi&>(acc->getStageObject()).deleteGuardColorAnim();
        // The egg-shield release effect spans all possible rotation angles.
        soEffectModule& effect = acc->getEffectModule();
        effect.req(static_cast<EfID>(0x50003), 0,
                   &Vec3f(0.0f, 0.0f, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), 1.0f,
                   &Vec3f(0.0f, 0.0f, 0.0f), &Vec3f(0.0f, 360.0f, 0.0f), false, 0);
    }
}
ftYoshiStatusUniqProcessEscapeFB g_ftYoshiStatusUniqProcessEscapeFB;
