#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
#include <cstdarg>
#include <cstddef>
#include <new>
#else
#include <stdarg.h>
#include <stddef.h>
#endif

#include <decomp.h>
#include <macros.h>

typedef unsigned long long u64;
typedef signed long long s64;

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

typedef float f32;
typedef double f64;

typedef int UNKWORD;
typedef void UNKTYPE;

enum { FALSE, TRUE };
typedef int BOOL;

typedef void (*funcptr_t)(void);

#if defined(__cplusplus) && __cplusplus < 201103L
namespace std {
class nullptr_t {
    void operator&() const;
public:
    template<typename T>
    operator T*() const { return 0; }

    template<typename C, typename T>
    operator T C::*() const { return 0; }
};
}

#ifdef __MWERKS__

#define ENUM_U8(name, ...) _Pragma("push") _Pragma("enumsalwaysint off") _Pragma("min_enum_size 1") enum name {  __VA_ARGS__ } _Pragma("pop")
#define ENUM_U16(name, ...) _Pragma("push") _Pragma("enumsalwaysint off") _Pragma("min_enum_size 2") enum name { __VA_ARGS__ } _Pragma("pop")
#define ENUM_U32(name, ...)  _Pragma("push") _Pragma("enumsalwaysint off") _Pragma("min_enum_size 4") enum name { __VA_ARGS__ } _Pragma("pop")

#define ENUM_S8(name, ...)  _Pragma("push") _Pragma("enumsalwaysint off") _Pragma("min_enum_size 1") enum name { _##name = -1, __VA_ARGS__ } _Pragma("pop")
#define ENUM_S16(name, ...) _Pragma("push") _Pragma("enumsalwaysint off") _Pragma("min_enum_size 2") enum name { _##name = -1, __VA_ARGS__ } _Pragma("pop")
#define ENUM_S32(name, ...)  _Pragma("push") _Pragma("enumsalwaysint off") _Pragma("min_enum_size 4") enum name { _##name = -1, __VA_ARGS__ } _Pragma("pop")

#else
#define ENUM_U8(name, ...) enum name : u8 { __VA_ARGS__ }
#define ENUM_U16(name, ...) enum name : u16 { __VA_ARGS__ }
#define ENUM_U32(name, ...) enum name : u32 { __VA_ARGS__ }

#define ENUM_S8(name, ...) enum name : s8 { __VA_ARGS__ }
#define ENUM_S16(name, ...) enum name : s16 { __VA_ARGS__ }
#define ENUM_S32(name, ...) enum name : s32 { __VA_ARGS__ }

#endif

const std::nullptr_t nullptr = {};
#endif

#endif
