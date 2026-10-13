#pragma once

#include <StaticAssert.h>
#include <types.h>

namespace hkMath {
    float fabs(float);
    float sqrt(float);
    float acos(float);
    float asin(float);

    template <class T>
    T min2(T val1, T val2) {
        if (val2 > val1) {
            return val1;
        }
        return val2;
    }

    template <class T>
    T max2(T val1, T val2) {
        if (val1 > val2) {
            return val1;
        }
        return val2;
    }
}