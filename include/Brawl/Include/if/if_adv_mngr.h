#pragma once

#include <types.h>

class IfAdvMngr {
public:
    s32 main();
    void renderPre();
};
// TODO size assertion

extern IfAdvMngr* g_IfAdvMngr;
