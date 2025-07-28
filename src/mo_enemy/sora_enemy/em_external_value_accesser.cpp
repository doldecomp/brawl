#include <em/em_external_value_accesser.h>
#include <em/em_weapon_manager.h>

Vec3f emExternalValueAccesser::getCenterPos(Enemy* em) {
    return em->getCenterPos();
}

bool emExternalValueAccesser::isCanGetRareItem(Enemy* em) {
    return soExternalValueAccesser::getModuleAccesser(em)
        ->getWorkManageModule().isFlag(0x1200000A);
}

float emExternalValueAccesser::getMaxHp(Enemy* em, u32 taskId) {
    if (taskId == -1 || taskId == em->m_taskId) {
        return soExternalValueAccesser::getModuleAccesser(em)
            ->getWorkManageModule().getFloat(0x11000003);
    }

    wnemSimple* wn = emWeaponManager::getInstance()->GetManagedWeaponFromTaskID(taskId);
    if (!wn) {
        return soExternalValueAccesser::getModuleAccesser(em)
            ->getWorkManageModule().getFloat(0x11000003);
    }
    return wn->unk21D8;
}

float emExternalValueAccesser::getHp(Enemy* em, u32 taskId) {
    if (taskId == -1 || taskId == em->m_taskId) {
        return soExternalValueAccesser::getModuleAccesser(em)
            ->getWorkManageModule().getFloat(0x11000001);
    }

    wnemSimple* wn = emWeaponManager::getInstance()->GetManagedWeaponFromTaskID(taskId);
    if (!wn) {
        return soExternalValueAccesser::getModuleAccesser(em)
            ->getWorkManageModule().getFloat(0x11000001);
    }
    return wn->unk21D4;
}

s32 emExternalValueAccesser::getNameMsgId(Enemy* em, u32 taskId) {
    if (taskId == -1 || taskId == em->m_taskId) {
        return em->getNameMsgId();
    }

    wnemSimple* wn = emWeaponManager::getInstance()->GetManagedWeaponFromTaskID(taskId);
    if (!wn) {
        return em->getNameMsgId();
    }

    if (wn->unk21E8 < 0) {
        return em->getNameMsgId();
    }
    return wn->unk21E8;
}

// NONMATCHING
nw4r::g3d::ResFileData* emExternalValueAccesser::getFaceTexPtr(Enemy* em, u32 taskId) {
    if (taskId == -1 || taskId == em->m_taskId) {
        return em->getFaceTexPtr();
    }

    const wnemSimple* wn = emWeaponManager::getInstance()->GetManagedWeaponFromTaskID(taskId);
    return (!wn) ? em->getFaceTexPtr() : em->getFaceTexPtr(wn->unk21EC);
}

float emExternalValueAccesser::getScore(Enemy* em) {
    return em->getScore();
}

bool emExternalValueAccesser::isFigure(Enemy* em) {
    return soExternalValueAccesser::getModuleAccesser(em)
        ->getWorkManageModule().isFlag(0x1200000F);
}

bool emExternalValueAccesser::isClipIn(Enemy* em) {
    return soExternalValueAccesser::getModuleAccesser(em)
        ->getCameraModule().isClipIn(false);
}

bool emExternalValueAccesser::isCanAutoRemove(Enemy* em) {
    return em->isCanAutoRemove();
}

s32 emExternalValueAccesser::getHitStopFrame(Enemy* em) {
    return soExternalValueAccesser::getModuleAccesser(em)
        ->getStopModule().getHitStopRealFrame();
}
