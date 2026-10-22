#pragma once

#include <StaticAssert.h>
#include <types.h>

struct gfSlowRequestId {
    u8 m_id;
};

class gfSlowManager {
    static const u32 StateInactive = 0;
    static const u32 StateActive = 1;
    struct SlowRequest {
        u8 m_state : 8;
        u8 m_slowRate;
    };

    static const u32 NRequests = 16;
    SlowRequest m_reqs[NRequests];
public:
    static void reset();
    // Set the global slow rate to the highest rate requested
    static void update();
    static gfSlowRequestId requestSlow(u8 rate);
    static bool removeRequest(const u8& idx);
    static u8 getSlowRate();
    static u8 getSlowRate(const u8& idx);
    static float getQuickRate();
    static float getRealTimeRate();
};
// TODO: size assertion
