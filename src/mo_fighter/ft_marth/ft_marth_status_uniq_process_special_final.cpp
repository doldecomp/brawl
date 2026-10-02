#include <types.h>

extern "C" {

void fn_106_CD00(float* dst, float x, float y);
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

}
