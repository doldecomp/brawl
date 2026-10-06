#include <types.h>
#include <stdio.h>
#include <string.h>

extern const char lbl_80489450[];

s32 DWC_SetCommonKeyValueString(const char* key, const char* value, char* text, char delimiter) {
    snprintf(text, 0x1000, lbl_80489450, delimiter, key, delimiter, value);
    return strlen(text);
}

s32 DWC_AddCommonKeyValueString(const char* key, const char* value, char* text, char delimiter) {
    char* end = strchr(text, 0);
    snprintf(end, 0x1000, lbl_80489450, delimiter, key, delimiter, value);
    (void)strlen(end);
    return strlen(text);
}

s32 DWC_GetCommonValueString(const char* key, char* value, const char* text, char delimiter) {
    const char* field;
    if (value == NULL) return -1;
    for (field = strchr(text, delimiter); field != NULL; field = strchr(field + 1, delimiter)) {
        if (strncmp(field + 1, key, strlen(key)) == 0 && field[strlen(key) + 1] == delimiter) {
            const char* end;
            u32 length;
            field = strchr(field + 1, delimiter);
            if (field == NULL) return -1;
            end = strchr(field + 1, delimiter);
            length = end == NULL ? strlen(field + 1) : end - (field + 1);
            strncpy(value, field + 1, length);
            value[length] = 0;
            return length;
        }
        field = strchr(field + 1, delimiter);
        if (field == NULL) return -1;
    }
    return -1;
}

typedef struct DWCRandomState {
    u64 value;
    u64 multiplier;
    u64 increment;
} DWCRandomState;

extern DWCRandomState lbl_80533718;
extern void fn_80390010(u8* address);
extern u64 OSGetTime(void);

u32 DWCi_GetMathRand32(u32 maximum) {
    u32 value;
    if (lbl_80533718.value == 0 && lbl_80533718.multiplier == 0 && lbl_80533718.increment == 0) {
        u8 address[8];
        fn_80390010(address);
        lbl_80533718.value = (OSGetTime() << 24) | ((u32)address[2] << 16) |
                            ((u32)address[3] << 8) | address[4];
        lbl_80533718.multiplier = 0x5D588B656C078965ULL;
        lbl_80533718.increment = 0x269EC3;
    }
    lbl_80533718.value = lbl_80533718.value * lbl_80533718.multiplier + lbl_80533718.increment;
    value = lbl_80533718.value >> 32;
    if (maximum != 0) value = ((u64)value * maximum) >> 32;
    return value;
}

s32 DWCi_WStrLen(const u16* text) {
    s32 length = 0;
    while (*text != 0) {
        ++text;
        ++length;
    }
    return length;
}
