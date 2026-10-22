#pragma once

#include <StaticAssert.h>
#include <gf/gf_camera.h>
#include <types.h>

class gfCameraController {
protected:
    gfCameraManager* m_cameraManager;

public:
    gfCameraController() : m_cameraManager(nullptr) { }
    virtual void update(float) = 0;
    virtual void draw();
};
static_assert(sizeof(gfCameraController) == 8, "Class is wrong size!");
