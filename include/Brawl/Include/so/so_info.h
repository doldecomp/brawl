#pragma once

#include <StaticAssert.h>
#include <types.h>

class soInfo {
public:
    virtual ~soInfo() { }
    virtual bool isInvalidKind(int kind) = 0;
    virtual int getInvalidKind() = 0;
    virtual const char* getNamePtr(int kind) = 0;
    virtual u32 getMotionNum(int kind) = 0;
    virtual u32 getStatusNum(int kind) = 0;

};
static_assert(sizeof(soInfo) == 0x4, "Class has the wrong size!");
