#pragma once

#include <gr/gr_yakumono.h>

class grMansion : public grYakumono {
protected:
    u8 unk150;
    float unk154;

public:
    static grMansion* create(int modelIndex, const char* nodeName, const char* taskName);
    grMansion(const char* taskName);
    virtual ~grMansion();
};
static_assert(sizeof(grMansion) == 0x158, "Class is wrong size!");
