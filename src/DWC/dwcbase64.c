#include <types.h>
#include <string.h>

extern const char* lbl_8059F058;
extern void fn_8034F028(void* destination, const void* source, u32 size);

s32 DWC_Base64Encode(const void* source, u32 size, void* destination, u32 capacity) {
    const u8* input = (const u8*)source;
    const u8* end = input + size;
    u8* output = (u8*)destination;
    u32 required = (size / 3) * 4 + (size % 3 != 0 ? 4 : 0);
    if (destination == NULL) return required;
    if (capacity < required) return -1;
    while (input != end) {
        u8 bytes[3];
        u32 remaining = end - input;
        u32 digits = (remaining * 8) / 6 + ((remaining * 8) % 6 != 0);
        u32 count = remaining < 3 ? remaining : 3;
        memset(bytes, 0, 3);
        fn_8034F028(bytes, input, count);
        output[0] = lbl_8059F058[bytes[0] >> 2];
        output[1] = digits < 2 ? '*' : lbl_8059F058[((bytes[0] & 3) << 4) | (bytes[1] >> 4)];
        output[2] = digits < 3 ? '*' : lbl_8059F058[((bytes[1] & 15) << 2) | (bytes[2] >> 6)];
        output[3] = digits < 4 ? '*' : lbl_8059F058[bytes[2] & 63];
        input += count;
        output += 4;
    }
    return output - (u8*)destination;
}

s32 DWC_Base64Decode(const char* source, u32 size, void* destination, u32 capacity) {
    s32 bits = 0;
    s32 required;
    u32 i;
    u8* output = (u8*)destination;
    if (size & 3) return -1;
    for (i = 0; i < size; ++i) {
        if (source[i] != '*') bits += 6;
    }
    required = bits / 8;
    if (destination == NULL) return required;
    if (capacity < (u32)required) return -1;
    if (size == 0) {
        *output = 0;
        return 0;
    }
    do {
        char values[4];
        for (i = 0; i < 4; ++i) {
            char ch = source[i];
            if (ch >= 'A' && ch <= 'Z') values[i] = ch - 'A';
            else if (ch >= 'a' && ch <= 'z') values[i] = ch - 'a' + 26;
            else if (ch >= '0' && ch <= '9') values[i] = ch - '0' + 52;
            else if (ch == '.') values[i] = 62;
            else if (ch == '-') values[i] = 63;
            else values[i] = 0;
        }
        source += 4;
        output[0] = (values[0] << 2) | (values[1] >> 4);
        if (output + 1 - (u8*)destination >= required) return output + 1 - (u8*)destination;
        output[1] = (values[1] << 4) | (values[2] >> 2);
        if (output + 2 - (u8*)destination >= required) return output + 2 - (u8*)destination;
        output[2] = (values[2] << 6) | values[3];
        output += 3;
    } while (output - (u8*)destination < required);
    return output - (u8*)destination;
}
