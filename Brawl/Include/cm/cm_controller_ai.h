#pragma once

#include <gf/gf_camera_controller.h>
#include <mt/mt_vector.h>

class cmAIController : public gfCameraController {
public:
    char _0x8[0xA8];
    Vec2f m_devilOffset;
    char _0xb8[0xE0];

    virtual void update(float p1);
    virtual void draw();
    virtual ~cmAIController();
    virtual void updateCameraPosTarget();

    void updateMeleeFix(float p1);
    void resetDevilOffset();
    void accDevilOffset(Vec2f*);

};
static_assert(sizeof(cmAIController) == 0x198, "Class is wrong size!");

extern cmAIController* g_cmAIController;
