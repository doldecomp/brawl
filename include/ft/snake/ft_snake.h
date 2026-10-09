#pragma once

#include <mt/mt_vector.h>

class soModuleAccesser;

// Interface-only declaration for the native static cursor helper. The full
// fighter builder layout remains outside this translation unit.
class ftSnake {
public:
    static void syncFinalCursorRate(Vec2f* cursor, soModuleAccesser* accesser);
};
