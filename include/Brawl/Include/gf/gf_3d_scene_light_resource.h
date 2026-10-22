#pragma once

#include <StaticAssert.h>
#include <nw4r/g3d/g3d_light.h>
#include <types.h>

class gfLightResHandle {
    u8 unk0;
public:
    nw4r::g3d::LightObj* getCharacterLight();
    void setZoneLightSet(u8 p1);
};
static_assert(sizeof(gfLightResHandle) == 1, "Class is the wrong size!");
