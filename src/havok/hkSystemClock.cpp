#include <havok/hkSystemClock.h>
#include <revolution/OS.h>

struct hkNgcSystemClock : hkSystemClock {
    long long getTickCounter() {
        return OSGetTime();
    }
    long long getTicksPerSecond() {
        return OS_TIME_SPEED;
    }
};

hkSystemClock* hkSystemClock::create() {
    return new hkNgcSystemClock();
}

static hkSingletonInitNode hkSystemClock_initNode((void* (*)())hkSystemClock::create,
                                                  (void**)&hkSingleton<hkSystemClock>::s_instance);

template <>
hkSystemClock* hkSingleton<hkSystemClock>::s_instance = 0;
