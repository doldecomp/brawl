#include <havok/hkMemory.h>
#include <havok/hkString.h>
#include <stdio.h>
#include <string.h>

#pragma dont_inline on
char hkString::toLower(char c) {
    bool upper = false;
    if (c >= 'A' && c <= 'Z') {
        upper = true;
    }
    if (upper) {
        return c + 0x20;
    }
    return c;
}
#pragma dont_inline reset

#pragma dont_inline on
int hkString::vsnprintf(char* buf, int len, const char* fmt, va_list args) {
    va_list copy;
    memCpy(&copy, args, sizeof(va_list));
    return ::vsnprintf(buf, len, fmt, copy);
}

#pragma dont_inline reset

int hkString::snprintf(char* buf, int len, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int r = ::vsnprintf(buf, len, fmt, args);
    va_end(args);
    return r;
}

int hkString::sprintf(char* buf, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int r = ::vsprintf(buf, fmt, args);
    va_end(args);
    return r;
}

int hkString::strCmp(const char* a, const char* b) {
    return ::strcmp(a, b);
}

int hkString::strCasecmp(const char* a, const char* b) {
    for (int i = 0; a[i] != 0 || b[i] != 0; i++) {
        int ca = toLower(b[i]);
        int cb = toLower(a[i]);
        if (cb < ca) {
            return -1;
        }
        ca = toLower(b[i]);
        cb = toLower(a[i]);
        if (cb > ca) {
            return 1;
        }
    }
    return 0;
}

int hkString::strLen(const char* s) {
    return ::strlen(s);
}

void* hkString::memCpy(void* dst, const void* src, int nbytes) {
    return ::memcpy(dst, src, nbytes);
}

struct hkBlock16 {
    int a, b, c, d;
};

void hkString::memCpy16(void* dst, const void* src, int numBlocks) {
    int i;
    for (i = 0; i < numBlocks; i++) {
        *(hkBlock16*)dst = *(const hkBlock16*)src;
        dst = (hkBlock16*)dst + 1;
        src = (const hkBlock16*)src + 1;
    }
}

void* hkString::memMove(void* dst, const void* src, int nbytes) {
    return ::memmove(dst, src, nbytes);
}

void* hkString::memSet(void* dst, int value, int nbytes) {
    return ::memset(dst, value, nbytes);
}

void hkString::Rep::freeMemory(Rep* rep) {
    hkMemory::getInstance().deallocateChunk(rep, rep->m_capacity + 0xD, 0x14);
}

hkString::Rep* hkString::Rep::create(int length) {
    int cap = length;
    if (cap < 0x33) {
        cap = 0x33;
    }
    Rep* rep = (Rep*)hkMemory::getInstance().allocateChunk(cap + 0xD, 0x14);
    rep->m_length = length;
    rep->m_capacity = cap;
    rep->unk8 = 0;
    return rep;
}

hkBool hkString::beginsWith(const char* prefix) const {
    long i = 0;
    while (*prefix != 0) {
        // MATCH-ONLY: reference temporary pins the load order
        __typeof__(m_string[i])& tmp0 = m_string[i];
        if (i >= ((int*)m_string)[-3] || tmp0 != *prefix) {
            return hkBool(false);
        }
        i++;
        prefix++;
    }
    return hkBool(true);
}
