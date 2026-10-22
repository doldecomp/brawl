#pragma once

#include <StaticAssert.h>
#include <gf/gf_camera_controller.h>

class cmMeleeFixedController : public gfCameraController {
public:
    cmMeleeFixedController();
    ~cmMeleeFixedController();
    virtual void update(float p1);
};
static_assert(sizeof(cmMeleeFixedController) == 8, "Class is wrong size!");
