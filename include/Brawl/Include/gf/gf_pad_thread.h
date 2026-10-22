#pragma once

#include <gf/gf_thread.h>
#include <StaticAssert.h>

class gfPadReadThread : public gfThread {
    bool unk340;
public:
    virtual void run();
};
static_assert(sizeof(gfPadReadThread) == 0x348, "Class is the wrong size!");
