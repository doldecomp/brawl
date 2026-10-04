#include <ft/marth/ft_marth.h>
#include <gf/gf_task.h>
#include <so/so_module_accesser.h>
#include <so/so_photo_call_back.h>
#include <types.h>

extern "C" {

void fn_106_CD00(float* dst, float x, float y);
void fn_106_D0C8(void* self, soModuleAccesser* acc);
void fn_106_CF58(void* self, soModuleAccesser* acc);
void fn_106_CFC0(void* self, soModuleAccesser* acc, int status);
void fn_106_CFBC();
void fn_106_D400(const void** obj);

extern const void* lbl_106_data_5678[];

void fn_106_CD00(float* dst, float x, float y) {
    dst[0] = x;
    dst[1] = y;
}

void fn_106_CFBC() {}

void fn_106_D400(const void** obj) {
    *obj = lbl_106_data_5678;
}

void fn_106_CF58(void* self, soModuleAccesser* moduleAccesser) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
        case 0x120:
            fn_106_D0C8(self, moduleAccesser);
            break;
    }
}

void fn_106_CFC0(void* self, soModuleAccesser* moduleAccesser, int status) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
        case 0x120: {
            ftMarth* marth = dynamic_cast<ftMarth*>(&moduleAccesser->getStageObject());
            if (marth == NULL) {
                return;
            }
            ((soPhotoCallBack*)((u8*)marth + 0x8554))->removeCallBack();
            break;
        }
    }
    switch (status) {
        case 0x11e:
        case 0x11f:
        case 0x120:
            return;
        default: {
            int count = moduleAccesser->getWorkManageModule().getInt(0x20000016);
            for (int i = 0; i < count; i++) {
                gfTask::getTask(moduleAccesser->getWorkManageModule().getInt(0x20000004 + i))->exit();
            }
            break;
        }
    }
}

}
