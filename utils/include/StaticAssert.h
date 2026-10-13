#pragma once

#include <decomp.h>

#ifdef __MWERKS__
#define static_assert(cond, msg) __static_assert(cond, msg)
#endif

template <bool>
struct CompileTimeError;
template <>
struct CompileTimeError<true> {
};

#define UNIQUE_NAME(base) CONCAT(base, __LINE__)

#define STATIC_CHECK(expr)                       \
    inline void UNIQUE_NAME(StaticCheck)()       \
    {                                            \
        ((void)CompileTimeError<(expr) != 0>()); \
    }

#define PRINT_SIZEOF(typename)                 \
    inline void UNIQUE_NAME(PrintSizeOf)()     \
    {                                          \
        char(*__kaboom)[sizeof(typename)] = 1; \
    }
