#include <revolution/VF.h>

size_t VFipf_w_strlen(const wchar_t* str) {
    const wchar_t* it = str;
    ptrdiff_t diff;

    // Find end of string
    for (; *it != L'\0'; it++) {
        ;
    }

    // Calculate size
    diff = (uintptr_t)it - (uintptr_t)str;
    return diff >> 1;
}

wchar_t* VFipf_w_strcpy(wchar_t* dst, const wchar_t* src) {
    // Preserve original pointer
    wchar_t* work_dst = dst;

    for (; *work_dst = *src, *work_dst != L'\0'; src++, work_dst++) {
        ;
    }

    return dst;
}

int VFipf_w_strncmp(const wchar_t* s1, const wchar_t* s2, size_t n) {

    for (; n > 0; n--, s1++, s2++) {
        if (*s1 == '\0' || *s2 == '\0' || *s1 != *s2) {
            return *s1 - *s2;
        }
    }

    return 0;
}
