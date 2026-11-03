#include <revolution/VF.h>

int VFipf_toupper(int c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }

    return c;
}

void* VFipf_memcpy(void* dst, const void* src, size_t n) {
    // Preserve original pointer
    void* work_dst = dst;

    // Word-aligned copy
    if ((u32)work_dst % 4 == 0 && (u32)src % 4 == 0) {
        for (; n > 3; n -= 4) {
            *((u32*)work_dst)++ = *((u32*)src)++;
        }
    }

    // Unaligned copy
    for (; n > 0; n--) {
        *((u8*)work_dst)++ = *((u8*)src)++;
    }

    return dst;
}

void* VFipf_memset(void* dst, int ch, size_t n) {
    // Preserve original pointer
    void* work_dst = dst;

    // Align dest pointer
    for (; (u32)work_dst % 4 != 0 && n > 0; n--) {
        *((u8*)work_dst)++ = ch;
    }

    // Word aligned store
    for (; n > 3; n -= 4) {
        *((u32*)work_dst)++ = ch << 24 | ch << 16 | ch << 8 | ch;
    }

    // Unaligned store
    for (; n > 0; n--) {
        *((u8*)work_dst)++ = ch;
    }

    return dst;
}

size_t VFipf_strlen(const char* str) {
    const char* it = str;

    // Find end of string
    for (; *it != '\0'; it++) {
        ;
    }

    // Calculate size
    return (uintptr_t)it - (uintptr_t)str;
}

char* VFipf_strcpy(char* dst, const char* src) {
    // Preserve original pointer
    char* work_dst = dst;

    for (; *work_dst = *src, *work_dst != '\0'; src++, work_dst++) {
        ;
    }

    return dst;
}

int VFipf_strcmp(const char* s1, const char* s2) {
    const u8* b1 = (const u8*)s1;
    const u8* b2 = (const u8*)s2;

    for (; *b1 != '\0' && *b2 != '\0' && *b1 == *b2; b1++, b2++) {
        ;
    }

    return *b1 - *b2;
}

int VFipf_strncmp(const char* s1, const char* s2, size_t n) {
    const u8* b1 = (const u8*)s1;
    const u8* b2 = (const u8*)s2;

    for (; n > 0; n--, b1++, b2++) {
        if (*b1 == '\0' || *b2 == '\0' || *b1 != *b2) {
            return *b1 - *b2;
        }
    }

    return 0;
}
