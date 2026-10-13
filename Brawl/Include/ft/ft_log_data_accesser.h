#pragma once

#include <StaticAssert.h>
#include <types.h>

struct ftLogData {
    char _[0x1b0];
};
static_assert(sizeof(ftLogData) == 0x1b0, "Class is wrong size!");

class ftLogDataAccesser {
    char _[0x24c];
public:
    ftLogDataAccesser();
    ~ftLogDataAccesser();

    void addFloat(float val, u32, u32);
    void addInt(int val, u32, u32);

    float getFloat(u32, u32);
    int getInt(u32, u32);
    bool isFlag(u32, u32);

    void offFlag(u32, u32);
    void onFlag(u32, u32);
    void setFlag(bool, u32, u32);
    void setFloat(float, u32, u32);
    void setInt(int, u32, u32);

    void setup(ftLogData* logData);
    void reset();
};
static_assert(sizeof(ftLogDataAccesser) == 0x24c, "Class is wrong size!");
