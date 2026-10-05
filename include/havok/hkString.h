#pragma once

#include <havok/hkBase.h>
#include <stdarg.h>

struct hkString {
    // Reference counted string header; character data follows at +0x0C.
    struct Rep {
        int m_length;   // 0x00
        int m_capacity; // 0x04
        int unk8;       // 0x08

        static void freeMemory(Rep* rep);
        static Rep* create(int length);
    };

    char* m_string; // points at Rep + 0x0C

    static char toLower(char c);
    static int vsnprintf(char* buf, int len, const char* fmt, va_list args);
    static int snprintf(char* buf, int len, const char* fmt, ...);
    static int sprintf(char* buf, const char* fmt, ...);
    static int strCmp(const char* a, const char* b);
    static int strCasecmp(const char* a, const char* b);
    static int strLen(const char* s);
    static void* memCpy(void* dst, const void* src, int nbytes);
    static void memCpy16(void* dst, const void* src, int numBlocks);
    static void* memMove(void* dst, const void* src, int nbytes);
    static void* memSet(void* dst, int value, int nbytes);

    hkBool beginsWith(const char* prefix) const;
};
