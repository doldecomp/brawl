#pragma once

// Local copy of BrawlHeaders' ft/ft_log_data_accesser.h that shadows it (-I include comes first).
// The original only declares the size (0x24c); the member tables below come from the accessors'
// addressing in the sora_melee REL, so they can be written as real code.

#include <StaticAssert.h>
#include <types.h>

struct ftLogData {
    char _[0x1b0];
};
static_assert(sizeof(ftLogData) == 0x1b0, "Class is wrong size!");

// Per-fighter match statistics, addressed as (category, slot). Each category is a pointer into the
// matching section of ftLogData (see setup()).
class ftLogDataAccesser {
    // The three tables are one run of 117 pointers (setup() binds each to a section of ftLogData);
    // m_count[i] is the number of elements behind pointer i, used by reset().
    // HYPOTHESIS: the table sizes (22 floats, 75 ints, 20 flags) follow from the pointer runs in the constructor.
    float* m_floatTable[22]; // 0x000
    int* m_intTable[75];     // 0x058
    bool* m_flagTable[20];   // 0x184
    u8 m_count[117];         // 0x1d4
public:
    ftLogDataAccesser();
    ~ftLogDataAccesser();

    void addFloat(float val, u32 category, u32 slot);
    void addInt(int val, u32 category, u32 slot);

    float getFloat(u32 category, u32 slot);
    int getInt(u32 category, u32 slot);
    bool isFlag(u32 category, u32 slot);

    void offFlag(u32 category, u32 slot);
    void onFlag(u32 category, u32 slot);
    void setFlag(bool val, u32 category, u32 slot);
    void setFloat(float val, u32 category, u32 slot);
    void setInt(int val, u32 category, u32 slot);

    void setup(ftLogData* logData);
    void reset();
};
static_assert(sizeof(ftLogDataAccesser) == 0x24c, "Class is wrong size!");
