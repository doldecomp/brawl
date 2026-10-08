// MATCH-ONLY: original article callbacks use the unscheduled compiler policy.
#pragma scheduling off
#include <wn/sonic/wn_sonic_super_sonic.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <cm/cm_camera_controller.h>


void wnSonicSuperSonic::processUpdate() {
    Weapon::processUpdate();
    m_moduleAccesser->getWorkManageModule().setFloat(0.0f, 0x11000001);
    if (!m_moduleAccesser->getWorkManageModule().isFlag(0x12000003) &&
        m_moduleAccesser->getStatusModule().getStatusKind() == 1) {
        soModuleAccesser* acc = m_moduleAccesser;
        soWorkManageModule& work = acc->getWorkManageModule();
        int threshold = soValueAccesser::getConstantInt(acc, 0x5DC1, 0);
        threshold -= soValueAccesser::getConstantInt(acc, 0x5DC0, 0);
        if (work.getInt(0x20000000) <= threshold) {
            m_moduleAccesser->getWorkManageModule().onFlag(0x12000003);
            m_moduleAccesser->getEffectModule().reqCommon(0.0f, 0);
        }
    }
}

void wnSonicSuperSonic::updatePosture(bool update) {
    Weapon::updatePosture(update);
    Vec3f pos = m_moduleAccesser->getPostureModule().getPos();
    CameraController* camera = CameraController::getInstance();
    if (camera != nullptr) {
        // These existing camera fields bound article movement; their broader
        // camera meaning remains HYPOTHESIS pending the camera setter audit.
        if (pos.m_x < camera->unk158) pos.m_x = camera->unk158;
        else if (pos.m_x > camera->unk15C) pos.m_x = camera->unk15C;
        if (pos.m_y < camera->unk164) pos.m_y = camera->unk164;
        else if (pos.m_y > camera->unk160) pos.m_y = camera->unk160;
    }
    m_moduleAccesser->getPostureModule().setPos(&pos);
}

void wnSonicSuperSonic::notifyEventCollisionAttack(float power, soCollisionLog* log, soModuleAccesser* acc) {
    if (m_moduleAccesser->getWorkManageModule().getFloat(0x11000001) < power) {
        m_moduleAccesser->getWorkManageModule().setFloat(power, 0x11000001);
    }
    Weapon::notifyEventCollisionAttack(power, log, acc);
}

bool wnSonicSuperSonic::notifyEventCollisionAttackCheck(u32 flags) {
    if ((flags & 7) != 0) {
        if (m_moduleAccesser->getWorkManageModule().getFloat(0x11000001) > 0.0f) {
            setHitStop(m_moduleAccesser->getWorkManageModule().getFloat(0x11000001), 1.0f, 0);
            m_moduleAccesser->getControllerModule().setRumble(0xD, 0, false, -1);
        }
        return false;
    }
    return Weapon::notifyEventCollisionAttackCheck(flags);
}

int wnSonicSuperSonic::convertSonicNode(int nodeId) {
    switch (nodeId) {
    case 0x15: return 0x14;
    case 0x43: return 0x42;
    case 0x18: return 0x17;
    case 0x31: return 0x30;
    case 0x24: return 0x23;
    case 0x1C: return 0x1B;
    case 0x33: return 0x32;
    default: return -1;
    }
}

void wnSonicSuperSonic::notifyEventChangeStatus(int kind, int prevKind, soStatusData* data, soModuleAccesser* acc) {
    Weapon::notifyEventChangeStatus(kind, prevKind, data, acc);
    switch (kind) {
    case 0: setGroundShapeSafePosWithAncestor(); break;
    default: break;
    }
}
