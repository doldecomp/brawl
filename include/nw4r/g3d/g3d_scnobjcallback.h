#pragma once

#include <nw4r/g3d/g3d_scnobj.h>

// Callback interface used by game-owned scene callbacks. Timing and arguments
// follow the nw4r declaration; the empty defaults already existed in the units.
namespace nw4r { namespace g3d {
class IScnObjCallback {
public:
    virtual ~IScnObjCallback() {}
    virtual void ExecCallback_CALC_WORLD(ScnObj::Timing, ScnObj*, u32, void*) {}
    virtual void ExecCallback_CALC_MAT(ScnObj::Timing, ScnObj*, u32, void*) {}
    virtual void ExecCallback_CALC_VIEW(ScnObj::Timing, ScnObj*, u32, void*) {}
    virtual void ExecCallback_DRAW_OPA(ScnObj::Timing, ScnObj*, u32, void*) {}
    virtual void ExecCallback_DRAW_XLU(ScnObj::Timing, ScnObj*, u32, void*) {}
};
}}
