#pragma once

#include <havok/hkSingleton.h>

// Platform clock singleton.
struct hkSystemClock : hkSingleton<hkSystemClock> {
    virtual long long getTickCounter() = 0;     // 0x10
    virtual long long getTicksPerSecond() = 0;  // 0x14

    static hkSystemClock* create();
};
