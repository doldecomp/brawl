#pragma once

#include <StaticAssert.h>
#include <gf/gf_camera_controller.h>

class cmDefaultController : public gfCameraController {
public:
    virtual void update(float);
};
static_assert(sizeof(cmDefaultController) == 8, "Class is wrong size!");
