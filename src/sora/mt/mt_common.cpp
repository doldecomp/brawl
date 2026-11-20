#include <math.h>
#include <mt/mt_common.h>
#include <types.h>

float mtSqrtf(register float x) {
    if (x > 0.0f) {
        register float y;
#ifdef MATCHING
        asm {
            frsqrte y, x
        }
#else
        y = 1.0f / sqrtf(x);
#endif
        y = 0.5f * y * (3.0f - x * (y * y));
        y = 0.5f * y * (3.0f - x * (y * y));
        return y * x;
    }
    return 0.0f;
}

float rsqrtf(register float x) {
    if (x < FLT_EPSILON)
        return 0.0f;
    register float y;
#ifdef MATCHING
    asm {
        frsqrte y, x
    }
#else
    y = 1.0f / sqrtf(x);
#endif
    y = 0.5f * y * (3.0f - x * (y * y));
    y = 0.5f * y * (3.0f - x * (y * y));
    return y;
}
