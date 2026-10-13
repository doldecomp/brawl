#pragma once

#include <types.h>
#include <StaticAssert.h>
#include <so/color/so_color_flash.h>

class soColorLight : public soColorFlash {
public:
    virtual ~soColorLight();
    virtual void reset();
};
static_assert(sizeof(soColorLight) == 0x3C, "Class is the wrong size!");