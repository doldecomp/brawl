#pragma once

#include <StaticAssert.h>
#include <types.h>

s32 randi(s32 max);
float randf();
void srandi(s32 seed);
s32 randseed(void);
float randaf(void);

class mtRand {
public:
    virtual void init(s32 p1);
    virtual s32 generate();
    virtual float randf();
    virtual s32 getMax();
    virtual s32 randi();
    s32 getSeed() { return m_seed; }
    void setSeed(s32 seed) { m_seed = seed; }

    mtRand(s32 v) : m_seed(v) { }

private:
    s32 m_seed;
    static const s32 MultVal = 0x41C64E6D;
    static const s32 AddVal = 0x3039;
};
static_assert(sizeof(mtRand) == 0x8, "Class is the wrong size!");

struct mtPrngLog {
    static const u32 BacktraceLength = 2;

    u32 m_randVal;
    void* m_backtrace[BacktraceLength];
    float m_gameFrame;

    mtPrngLog(u32 val, void* sp);
};
static_assert(sizeof(mtPrngLog) == 0x10, "Class is the wrong size!");

struct mtPrngLogManager {
    u32 m_maxLen;
    u32 m_len;
    mtPrngLog* m_logs;

    mtPrngLogManager() : m_maxLen(0), m_len(0), m_logs(nullptr) { }
    ~mtPrngLogManager();
    bool addLog(const mtPrngLog* log);
};
static_assert(sizeof(mtPrngLogManager) == 0xC, "Class is the wrong size!");

extern mtPrngLogManager g_mtPrngLogManager;
