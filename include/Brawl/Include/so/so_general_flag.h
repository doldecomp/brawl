#pragma once

#include <StaticAssert.h>

template <typename T>
struct soGeneralFlag {
    T flag;
    soGeneralFlag(T init) : flag(init) { }
};
