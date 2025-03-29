#include <cm/cm_controller_ai.h>
#include <cm/cm_controller_melee_fixed.h>
#include <gf/gf_camera_controller.h>

cmMeleeFixedController::cmMeleeFixedController() : gfCameraController() { }

cmMeleeFixedController::~cmMeleeFixedController() { }

void cmMeleeFixedController::update(float p1) {
    g_cmAIController->updateMeleeFix(p1);
}
