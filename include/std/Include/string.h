#pragma once

#include "__mem.h"
#include "extras.h"
#include "stddef.h"
#include "strtoul.h"
#include "types.h"

class String {
    const char* m_string;

public:
    int strcmp(const String str2);
    static String strncpy(String destination, const char* source, size_t num);

    inline String(const char* ss)
    {
        m_string = ss;
    };

    // bool operator==(const String str2);

    inline String operator[](const u32 index)
    {
        String out = " ";
        return strncpy(out, &m_string[index], 1);
    };

    inline int length()
    {
        return strlen(m_string);
    }
    inline int stoi()
    {
        return atoi(m_string);
    };

    template <int I>
    inline static String to_string(int ii)
    {
        char ss[I];
        itoa(ii, ss, 10);
        String scoreStr(ss);
        return scoreStr;
    };
};

#ifdef __cplusplus
extern "C" {
#endif
char* strcat(char* output, const char* append);
char* strchr(char* str, int character);
char* strcpy(char* destination, const char* source);
int strcmp(const char* str1, const char* str2);
size_t strcspn(const char* str1, const char* str2);
char* strncat(char* output, const char* append, size_t num);
int strncmp(const char* str1, const char* str2, size_t num);
char* strncpy(char* destination, const char* source, size_t num);
char* strrchr(const char* str, int character);
char* strstr(const char* haystack, const char* needle);
char* strtok(char* str, const char* delimiters);
#ifdef __cplusplus
}
#endif