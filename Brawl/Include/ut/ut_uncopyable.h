#pragma once

#include <StaticAssert.h>
#include <types.h>

class utUnCopyable {
    utUnCopyable(const utUnCopyable&);
    utUnCopyable& operator=(const utUnCopyable&);
protected:
    utUnCopyable() { }
};
