#pragma once

#include <nw4r/ut/ut_Font.h>

struct FontData {
    enum FONT_RESOURCE {
        FONT_SYSTEM = 0,
        FONT_NORMAL = 1,
        FONT_HIRAGANA = 2,
        FONT_ENDING = 3,
        FONT_MELEE = 4,
        FONT_RESETSAN = 5,
        FONT_FOX = 6,
        FONT_ALERT = 7,
        FONT_NORMAL2 = 8,
    };

    static nw4r::ut::Font* getFontResource(int id);
    static void loadAlertFont(void* p1);
};
