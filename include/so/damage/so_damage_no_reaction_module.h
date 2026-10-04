#pragma once

#include <StaticAssert.h>
#include <types.h>

// NOTE: shadows the BrawlHeaders copy to add the member functions (names from the map).
class soDamageNoReactionModule {
public:
    int m_mode;
    int m_modeStatus;
    char _8[8];
    int m_modeStatus2nd;
    char _20[8];
    bool m_isModeAlways;
    bool m_isModePerfect;
    char _30[2];

public:
    void set(float unk1, float unk2, bool is2nd, int mode);
    void resetModeStatus();
    void setMode(int mode);
    void resetMode();
    void reset();
    bool checkNoReaction(float reaction, float powerMax, bool isAbsolute);
};
static_assert(sizeof(soDamageNoReactionModule) == 32, "Class is wrong size!");