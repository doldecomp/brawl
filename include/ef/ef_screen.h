#pragma once

// Shadows the BrawlHeaders declaration to expose the verified flash request.
#include <GX.h>
#include <types.h>

class efScreen {
    char _spacer[492];

public:
    int requestFill(float, int, int, GXColor*);
    int requestFlash(float frames, int layer, u8 alpha, u32 cycles, GXColor* color);
    static efScreen* getInstance();
};

extern efScreen* g_efScreen;

inline efScreen* efScreen::getInstance() { return g_efScreen; }
