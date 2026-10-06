#include <types.h>

extern s32 lbl_805A0F48;
extern s32 lbl_805A0F4C;

s32 DWC_GetLastError(s32* code) {
    if (code != NULL) *code = lbl_805A0F4C;
    return lbl_805A0F48;
}

s32 DWC_GetLastErrorEx(s32* code, s32* type) {
    if (code != NULL) *code = lbl_805A0F4C;
    if (type != NULL) {
        switch (lbl_805A0F48) {
        case 1: case 9: *type = 7; break;
        case 2: case 3: case 4: case 5: case 8: *type = 6; break;
        case 6: *type = 3; break;
        case 7: *type = 4; break;
        case 10: case 11: case 12: case 13: *type = 1; break;
        case 14: *type = 5; break;
        case 15: case 17: case 20: *type = 6; break;
        case 16: case 18: case 21: *type = 2; break;
        case 19: *type = 1; break;
        default: *type = 0; break;
        }
    }
    return lbl_805A0F48;
}

void DWC_ClearError(void) {
    if (lbl_805A0F48 == 9) return;
    lbl_805A0F48 = 0;
    lbl_805A0F4C = 0;
}

BOOL DWCi_IsError(void) { return lbl_805A0F48 != 0; }

void DWCi_SetError(s32 error, s32 code) {
    if (lbl_805A0F48 == 9) return;
    lbl_805A0F48 = error;
    lbl_805A0F4C = code;
}
