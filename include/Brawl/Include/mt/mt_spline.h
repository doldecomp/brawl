#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <types.h>

void mtBezierCurve(float t, Vec3f points[4], Vec3f* outPoint);