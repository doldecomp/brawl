#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <mt/mt_vector.h>

namespace soGroundUtil {
    enum DeadAreaCheckResult {
        Dead_Area_Check_Result_None = -1,
        Dead_Area_Check_Result_Outside_Up = 0,
        Dead_Area_Check_Result_Outside_Down = 1,
        Dead_Area_Check_Result_Outside_Left = 2,
        Dead_Area_Check_Result_Outside_Right = 3,
    };

    DeadAreaCheckResult checkDeadArea(Vec3f* pos, float, float);
}