#pragma once

#include <StaticAssert.h>
#include <gf/gf_camera_controller.h>
#include <nw4r/g3d/g3d_anmscn.h>
#include <types.h>

class cmAnimationController : public gfCameraController {
    char _8[28];

public:
    virtual void update(float);

    bool setScnAnmRes(nw4r::g3d::ResAnmScn, u32);
    void releaseScnAnmRes();
};
static_assert(sizeof(cmAnimationController) == 0x24, "Class is wrong size!");
