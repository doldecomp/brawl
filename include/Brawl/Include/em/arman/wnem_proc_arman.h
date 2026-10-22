#pragma once

#include <so/so_module_accesser.h>
#include <wn/wn_em_simple.h>

class wnemArmanProc {
public:
    static void ArmEnter(wnemSimple* wn, soModuleAccesser* acc);
    static void ArmExit(wnemSimple* wn, soModuleAccesser* acc);
    static void ArmIdol(wnemSimple* wn);
    static void ArmDead(wnemSimple* wn, soModuleAccesser* acc);
};
