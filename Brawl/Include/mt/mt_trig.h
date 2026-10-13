#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <math.h>

float mtSinf(float angle);
float mtCosf(float angle);
void mtSinCosf(float rad, float* sinOut, float* cosOut);

template <class T>
T mtConvRadToDeg(T rad) {
    return rad*(180 / M_PI);
};

template <class T>
T mtConvDegToRad(T deg) {
    return deg*(M_PI / 180);
};