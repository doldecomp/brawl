#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/lucas/ft_lucas_status_uniq_process_special_hi.h>
#include <ft/ft_common_data_accesser.h>
#include <so/so_module_accesser.h>
// HYPOTHESIS: reflect duration resides at common-data+0x84+0x2C.
struct ftLucasReflectCommonParam { u8 unk00[0x2C]; float reflectDuration; };
struct ftLucasReflectCommonParamData { u8 unk00[0x84]; ftLucasReflectCommonParam* reflect; };
void ftLucasStatusUniqProcessSpecialHiReflect::exitStatus(soModuleAccesser* a, int nextStatus) {
    if (nextStatus != 0x10) return;
    ftLucasReflectCommonParam* param = reinterpret_cast<ftLucasReflectCommonParamData*>(
        g_ftCommonDataAccesser.getData(Fighter_Lucas))->reflect;
    if (param->reflectDuration > 0.0f)
        a->getWorkManageModule().onFlag(0x11000000);
}
ftLucasStatusUniqProcessSpecialHiReflect::~ftLucasStatusUniqProcessSpecialHiReflect() {}
ftLucasStatusUniqProcessSpecialHiReflect g_ftLucasStatusUniqProcessSpecialHiReflect;
