#pragma once

#include <StaticAssert.h>
#include <types.h>

class DWCAllocType {
public:
    static void* ntAlloc(int, u32, u32);
    static void ntFree(int, void*);
};
// TODO size assertion
