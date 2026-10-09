#pragma once

#include <mt/mt_vector.h>

class soRotUtility {
public:
    // Wrap each Euler component into the native rotation interval.
    static Vec3f clampDeg(const Vec3f& rotation);
};
