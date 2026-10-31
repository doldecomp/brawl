#include <revolution/VF.h>

void VFiPFSTR_SetCodeMode(PF_STR* str, u32 mode) { str->mode = mode; }

u32 VFiPFSTR_GetCodeMode(PF_STR* str) { return str->mode; }

void VFiPFSTR_SetLocalStr(PF_STR* str, char* local) {
    if (VFiPFSTR_GetCodeMode(str) == PFSTR_CODEMODE_OEM || local == NULL) {
        str->local = str->head;
    } else {
        str->local = local;
    }
}

char* VFiPFSTR_GetStrPos(PF_STR* str, u32 target) {
    if (target == PFSTR_CODEMODE_OEM) {
        return (char*)str->head;
    }

    if (target == PFSTR_CODEMODE_UNICODE) {
        return (char*)str->tail;
    }

    return (char*)str->local;
}

void VFiPFSTR_MoveStrPos(PF_STR* str, s16 n) {
    s16 i;
    s16 dist = 0;

    if (VFiPFSTR_GetCodeMode(str) == PFSTR_CODEMODE_OEM) {
        const char* data = (const char*)str->head;

        for (; n != 0; dist++, n--) {
            if (VFipf_vol_set.codeset.is_oem_mb_char(*data, 1)) {
                dist++;
            }
        }
    } else {
        wchar_t* data = (wchar_t*)str->head;

        for (i = 0; i < n; i++) {
            const size_t width = VFipf_vol_set.codeset.unicode_char_width(data);
            data += width;
            dist += (s16)width;
        }
    }

    str->head += dist;
}

s32 VFiPFSTR_InitStr(PF_STR* str, const char* s, u32 mode) {
    if (str == NULL || s == NULL) {
        return PF_RESULT_INVALID;
    }

    if (mode == PFSTR_CODEMODE_OEM) {
        str->head = s;
        str->tail = s + VFipf_strlen(s);
    } else if (mode == PFSTR_CODEMODE_UNICODE) {
        str->head = s;
        str->tail = s + VFipf_w_strlen((wchar_t*)s) * sizeof(wchar_t);
    } else {
        return PF_RESULT_INVALID;
    }

    VFiPFSTR_SetCodeMode(str, mode);
    return PF_RESULT_OK;
}

u16 VFiPFSTR_StrLen(PF_STR* str) {
    return (uintptr_t)str->tail - (uintptr_t)str->head;
}

u16 VFiPFSTR_StrNumChar(PF_STR* str, u32 target) {
    const char* data;
    size_t width;
    u16 length;

    if (target == PFSTR_CODEMODE_OEM) {
        data = str->head;
    } else {
        data = str->tail;
    }

    if (VFiPFSTR_GetCodeMode(str) == PFSTR_CODEMODE_OEM) {
        length = 0;
        for (; *data != '\0'; data++, length++) {
            if (VFipf_vol_set.codeset.is_oem_mb_char(*data,
                                                     PFSTR_CODEMODE_OEM)) {
                data++;
            }
        }
    } else {
        length = 0;
        for (; data[0] != '\0' || data[1] != '\0'; data += width, length++) {
            width = VFipf_vol_set.codeset.unicode_char_width((wchar_t*)data);
        }
    }

    return length;
}

s32 VFiPFSTR_StrCmp(const PF_STR* str, const char* cmp) {
    const wchar_t* data;
    wchar_t out;

    if (VFiPFSTR_GetCodeMode((PF_STR*)str) == PFSTR_CODEMODE_OEM) {
        return VFipf_strcmp(str->head, cmp);
    }

    data = (const wchar_t*)str->head;
    do {
        VFipf_vol_set.codeset.oem2unicode((char*)cmp, &out);
        cmp++;
    } while (*data++ == out && data[-1] != L'\0' && out != L'\0');

    return data[-1] - out;
}

int VFiPFSTR_StrNCmp(PF_STR* str, const char* cmp, u32 target, s16 offset,
                     u16 n) {
    const wchar_t* wdata;
    const char* data;
    wchar_t out;

    if (VFiPFSTR_GetCodeMode(str) == PFSTR_CODEMODE_OEM ||
        target == PFSTR_CODEMODE_LOCAL) {

        if (target == PFSTR_CODEMODE_OEM) {
            data = str->head + offset;
        } else if (target == PFSTR_CODEMODE_UNICODE) {
            data = str->tail + offset;
        } else {
            data = str->local + offset;
        }

        return VFipf_strncmp(data, cmp, n);
    }

    if (target == PFSTR_CODEMODE_OEM) {
        wdata = (wchar_t*)(str->head + offset * sizeof(wchar_t));
    } else {
        wdata = (wchar_t*)(str->tail + offset * sizeof(wchar_t));
    }

    do {
        VFipf_vol_set.codeset.oem2unicode((char*)cmp, &out);
        cmp++;
        n--;
    } while (*wdata++ == out && n > 0 && wdata[-1] != L'\0' && out != L'\0');

    return wdata[-1] - out;
}

void VFiPFSTR_ToUpperNStr(PF_STR* str, u16 n, char* out) {
    const char* data;
    const wchar_t* wdata;
    u32 ch;
    BOOL letter;

    if (str->mode == PFSTR_CODEMODE_OEM) {
        for (data = (const char*)str->head; n > 0 && *data != '\0';
             data++, n--) {
            *out++ = VFipf_toupper(*data);
        }
    } else {
        for (wdata = (const wchar_t*)str->head; n > 0 && *wdata != L'\0';
             n--, wdata++) {
            letter = *wdata >= 'a' && *wdata <= 'z';

            if (letter) {
                ch = *wdata - ('a' - 'A');
            } else {
                ch = *wdata;
            }

            out[0] = ch >> 0 & 0xFF;
            out[1] = ch >> 8 & 0xFF;
            out += sizeof(wchar_t);
        }

        *out = '\0';
    }

    *out = '\0';
}
