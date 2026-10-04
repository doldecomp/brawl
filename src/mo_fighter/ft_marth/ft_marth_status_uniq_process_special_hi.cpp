#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

extern "C" {

double fn_106_BE30(double value);
void fn_106_BE40(void* self, soModuleAccesser* acc);
bool fn_106_BEE4(void* self, soModuleAccesser* acc, float, float);
void fn_106_BE38();
void fn_106_BE3C();
void fn_106_BFE0(const void** obj);

extern const void* lbl_106_data_5584[];

double fn_106_BE30(double value) {
    return __fabs(value);
}

void fn_106_BE38() {}

void fn_106_BE3C() {}

void fn_106_BFE0(const void** obj) {
    *obj = lbl_106_data_5584;
}

void fn_106_BE40(void* self, soModuleAccesser* moduleAccesser) {
    float a = soValueAccesser::getConstantFloat(moduleAccesser, 0xfa8, 0);
    moduleAccesser->getWorkManageModule().setFloat(a, 0x11000000);
    float b = soValueAccesser::getConstantFloat(moduleAccesser, 0xfa7, 0);
    moduleAccesser->getWorkManageModule().setFloat(b, 0x11000001);
    moduleAccesser->getWorkManageModule().onFlag(0x12000003);
}

bool fn_106_BEE4(void* self, soModuleAccesser* moduleAccesser, float, float) {
    moduleAccesser->getWorkManageModule().setFloat(0.0f, 0x21000004);
    moduleAccesser->getWorkManageModule().onFlag(0x22000016);
    return true;
}

}
