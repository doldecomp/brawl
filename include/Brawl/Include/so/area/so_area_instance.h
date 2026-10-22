#pragma once

#include <StaticAssert.h>
#include <types.h>

class soAreaInstance {
public:
    enum ShapeType {
        Shape_Rectangle = 0x0,
        Shape_Circle = 0x1,
        Shape_Rectangle_Ref_Ground_Rhombus = 0x2,
        Shape_Rectangle_Ref_Ground_Rhombus_Upper = 0x3,
        Shape_Rectangle_Ref_Ground_Rhombus_Lower = 0x4,
    };

private:
    char _0[32];
public:

    virtual ~soAreaInstance();
};
static_assert(sizeof(soAreaInstance) == 36, "Class is wrong size!");