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
    u16 flags = camera->unkFA.m_mask;
    u16 flagsWith7 = flags | 0x80;
    u16 flagsWith7And1 = flags | 0x82;
    camera->unkFA.m_mask = flagsWith7;
    camera->m_targetPos.m_x = unk10.m_x;
    camera->m_targetPos.m_y = unk10.m_y;
    camera->m_targetPos.m_z = unk10.m_z;
    camera->unkFA.m_mask = flagsWith7And1;
    camera->unkD0 = unk1C;
    Vec2f rot(0.0f, 0.0f);
    camera->m_rot.m_x = rot.m_x;
    camera->m_rot.m_y = rot.m_y;
    camera->m_rot.m_z = 0.0f;
    camera->unkFA.m_mask |= 0x40;
}

extern "C" void fn_80018778(gfCamera*);

void cmMenuFixedController::update(float) {
    gfCamera* camera;
    gfCamera* cachedCamera = &m_cameraManager->m_cameras[0];
    if (!unk8) {
        unkC = cachedCamera->unkCC;
        unk10.m_x = cachedCamera->m_targetPos.m_x;
        unk10.m_y = cachedCamera->m_targetPos.m_y;
        unk10.m_z = cachedCamera->m_targetPos.m_z;
        unk1C = cachedCamera->unkD0;
        unk8 = true;
    }
    camera = &m_cameraManager->m_cameras[0];
    camera->unkCC = unkC;
    u16 flags = camera->unkFA.m_mask;
    u16 flagsWith7 = flags | 0x80;
    u16 flagsWith7And1 = flags | 0x82;
    camera->unkFA.m_mask = flagsWith7;
    camera->m_targetPos.m_x = unk10.m_x;
    camera->m_targetPos.m_y = unk10.m_y;
    camera->m_targetPos.m_z = unk10.m_z;
    camera->unkFA.m_mask = flagsWith7And1;
    camera->unkD0 = unk1C;
    Vec2f rot(0.0f, 0.0f);
    camera->m_rot.m_x = rot.m_x;
    camera->m_rot.m_y = rot.m_y;
    camera->m_rot.m_z = 0.0f;
    camera->unkFA.m_mask |= 0x40;
    cachedCamera->m_transformFlag.m_mask = 0xE1;
    fn_80018778(cachedCamera);
}
