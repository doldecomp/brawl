#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <types.h>

class cmQuake {
public:
    enum Amplitude {
        Amplitude_None = 0x0,
        Amplitude_M = 0x1,
        Amplitude_Middle = 0x1,
        Amplitude_S_Half = 0x2,
        Amplitude_Small_Hf = 0x2,
        Amplitude_S = 0x3,
        Amplitude_Small = 0x3,
        Amplitude_L = 0x4,
        Amplitude_Large = 0x4,
        Amplitude_XL = 0x5,
        Amplitude_More_Large = 0x5,
    };

    char _[0x274];
};
static_assert(sizeof(cmQuake) == 0x274, "Class is wrong size!");

void cmReqQuake(cmQuake::Amplitude amplitude, Vec3f* offset);
void cmRemoveQuake(int index);