#include <gf/gf_camera_controller.h>

void gfCameraController::draw() {
    m_cameraManager->getCamera(0)->renderDebug();
}
