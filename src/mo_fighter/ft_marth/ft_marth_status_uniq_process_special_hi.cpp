#include <types.h>

extern "C" {

double fn_106_BE30(double value);
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

}
