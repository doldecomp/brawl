#include <StaticAssert.h>
#include <gf/gf_camera.h>
#include <gf/gf_camera_controller.h>
#include <types.h>

class cmMenuFixedController : public gfCameraController {
    bool unk8 : 1;
    float unkC;
    Vec3f unk10;
    float unk1C;
public:
    cmMenuFixedController();
    void storeDefault();
    void init();
    virtual void update(float);
};
static_assert(sizeof(cmMenuFixedController) == 0x20, "Class is wrong size!");

cmMenuFixedController::cmMenuFixedController() : gfCameraController() {
    unkC = 68.0f;
    unk1C = 0.69813f;
    unk8 = false;
    unk10.m_x = 0.0f;
    unk10.m_y = 0.0f;
    unk10.m_z = 0.0f;
}

void cmMenuFixedController::storeDefault() {
    unkC = m_cameraManager->m_cameras[0].unkCC;
    unk10.m_x = m_cameraManager->m_cameras[0].m_targetPos.m_x;
    unk10.m_y = m_cameraManager->m_cameras[0].m_targetPos.m_y;
    unk10.m_z = m_cameraManager->m_cameras[0].m_targetPos.m_z;
    unk1C = m_cameraManager->m_cameras[0].unkD0;
    unk8 = true;
}

void cmMenuFixedController::init() {
    gfCamera* camera = &m_cameraManager->m_cameras[0];
    camera->unkCC = unkC;
    camera->unkFA.m_mask |= 0x80;
    camera->m_targetPos = unk10;
    camera->unkFA.m_mask |= 0x2;
    camera->unkD0 = unk1C;
    *camera->m_rot.xy() = Vec2f(0.0f, 0.0f);
    camera->m_rot.m_z = 0.0f;
    camera->unkFA.m_mask |= 0x40;
}

void cmMenuFixedController::update(float) {
    gfCamera* camera = &m_cameraManager->m_cameras[0];
    if (!unk8) {
        storeDefault();
    }
    init();
    camera->m_transformFlag.m_mask = 0xe1;
    camera->calc();
}
