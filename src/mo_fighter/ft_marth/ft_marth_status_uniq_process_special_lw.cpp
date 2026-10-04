#include <types.h>

extern "C" {

void fn_106_C390(u8* obj, const float* src);
void fn_106_C674();
void fn_106_C98C(const void** obj);

extern const void* lbl_106_data_5600[];

void fn_106_C390(u8* obj, const float* src) {
    *(float*) (obj + 32) = src[0];
    *(float*) (obj + 36) = src[1];
}

void fn_106_C674() {}

void fn_106_C98C(const void** obj) {
    *obj = lbl_106_data_5600;
}

}
