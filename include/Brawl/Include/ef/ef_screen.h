#pragma once

#include <StaticAssert.h>
#include <GX.h>
#include <types.h>

class efScreen;
extern efScreen* g_efScreen;
class efScreen {
    char _spacer[492];

public:
    int requestFill(float, int, int, GXColor*);

    inline static efScreen* getInstance() { return g_efScreen; }
};

