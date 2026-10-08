// MATCH-ONLY: original article callbacks use the unscheduled compiler policy.
#pragma scheduling off
#define MT_VEC3F_CTOR_NOINLINE
#include <wn/sonic/wn_sonic_super_sonic.h>
#include <wn/wn_activate_desc.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <cm/cm_camera_controller.h>


void wnSonicSuperSonic::activate(int founderTaskId, int resourceId, int team, Vec2f* pos,
                               float lr, SituationKind situation, wnSonicSuperSonicEffectList* effects) {
    Vec3f position(pos->m_x, pos->m_y, 0.0f);
    wnActivateDesc desc;
    desc.founderTaskId = founderTaskId;
    desc.resourceId = resourceId;
    desc.unk8 = resourceId;
    desc.unkC = resourceId;
    desc.unk10 = -1;
    desc.unk14 = -1;
    desc.unk18 = 0;
    desc.unk1C = 0;
#ifdef MATCHING
    // MATCH-ONLY: retain the original aggregate word copy.
    __memcpy(&desc.pos, &position, sizeof(Vec3f));
#else
    desc.pos = position;
#endif
    desc.lr = lr;
    desc.team = team;
    desc.life = 0;
    desc.unk38 = 2;
    desc.unk3C = 0x80;
    desc.unk40 = 0;
    desc.unk44 = 0x35F;
    desc.unk48 = 0;
    // HYPOTHESIS: original named bitfields and the unused low six bits of 4D.
    // Only the activation bits consumed by Weapon::activate are reconstructed.
    desc.flags = 0xA0;
    desc.unk4D = 0;
    Weapon::activate(&desc);
    m_moduleAccesser->getWorkManageModule().onFlag(0x12000000);
    m_moduleAccesser->getCollisionHitModule().setWhole(3, 0);
    if (situation == Situation_Ground && m_moduleAccesser->getGroundModule().attachGround(0) == true) {
        m_moduleAccesser->getSituationModule().setKind(Situation_Ground, false);
    }
    m_moduleAccesser->getLinkModule().setAttribute(3, soLinkConnection::Attribute_Reference_Parent_Unknown_4, true);
    for (u32 i = 0; i < effects->size; ++i) {
        int node = convertSonicNode(effects->entries[i].nodeId);
        if (node != -1) {
            Vec3f pos = effects->entries[i].pos;
            Vec3f rot(0.0f, 0.0f, 0.0f);
            m_moduleAccesser->getEffectModule().reqFollow(static_cast<EfID>(0x1020002), node,
                                                       &pos, &rot, effects->entries[i].scale,
                                                       true, 0x10, 0, -1);
        }
    }
    m_moduleAccesser->getLinkModule().setAttribute(3, soLinkConnection::Attribute_Reference_Parent_Scale, true);
    u8 playerNo, pri, advPri;
    m_moduleAccesser->getLinkModule().getLinkParentCameraInfo(3, &playerNo, &pri, &advPri);
    m_moduleAccesser->getCameraModule().setPri(pri, -1);
    m_moduleAccesser->getCameraModule().setAdvPri(advPri, -1);
    m_moduleAccesser->getCameraModule().setPlayerNo(playerNo, 0);
    m_moduleAccesser->getGroundModule().setCorrect(soGroundShapeImpl::Correct_None, 0);
}

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
