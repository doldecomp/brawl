#include "internal/wstring.h"

int wcscmp(const wchar_t* s1, const wchar_t* s2) {
    wchar_t c1, c2;

    do
    {
        c1 = *s1++;
        c2 = *s2++;
        if (c2 == L'\0')
            return c1 - c2;
    }
    while (c1 == c2);

    return c1 < c2 ? -1 : 1;
};
