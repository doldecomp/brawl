#pragma once

#include <types.h>
#include <StaticAssert.h>
#include <so/color/so_color_flash.h>
#include <so/color/so_color_light.h>

class soColorBlend {
    soColorFlash m_flash;
    soColorLight m_light;
    char _0x78[0x10];
};
static_assert(sizeof(soColorBlend) == 0x88, "Class is the wrong size!");
