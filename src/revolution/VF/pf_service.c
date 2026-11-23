#include <revolution/VF.h>

u16 VFiPF_GET_LE_U16(const u8* buf) { return buf[0] | buf[1] << 8; }

void VFiPF_LE16_TO_U16_STR(u8* str, u32 n) {
    u32 i;

    for (i = 0; i < n; i += sizeof(u16)) {
        const char tmp = str[i];
        str[i] = str[i + 1];
        str[i + 1] = tmp;
    }
}
