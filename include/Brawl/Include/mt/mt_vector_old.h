#pragma once

#include <mt/mt_vector.h>
#include <types.h>

namespace vlRotateAxis {
    enum Enum {
        X = 1,
        Y = 2,
        Z = 4
    };
}

Vec3f* vlRotateFix(Vec3f* v, vlRotateAxis::Enum axis, float theta);
