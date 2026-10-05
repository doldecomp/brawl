#include <ft/fighter.h>
#include <ft/ft_kinetic_energy.h>
#include <ft/ft_status_uniq_process_cliff.h>
#include <math.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

// MATCH-ONLY: the original TU's RTTI for ftKineticEnergyMotion lives in another TU; calling the runtime
// directly avoids emitting a duplicate weak copy of the whole RTTI chain here.
extern "C" {
extern char __RTTI__21ftKineticEnergyMotion[];
extern char __RTTI__15soKineticEnergy[];
void* __dynamic_cast(void* ptr, long vtblOffset, const void* target, const void* source, int isRef);
}

ftStatusUniqProcessCliff g_ftStatusUniqProcessCliff;

void ftStatusUniqProcessCliff::initStatus(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getGroundModule().isStCliff(0) == true) {
        int kind = moduleAccesser->getStatusModule().getStatusKind();
        bool a = true;
        bool b = false;
        switch (kind) {
        case Fighter::Status::Cliff_Catch: {
            float lr = moduleAccesser->getPostureModule().getLr();
            Vec3f cliffPos = moduleAccesser->getGroundModule().getCliffPos(0);
            Vec3f pos = moduleAccesser->getPostureModule().getPos();
            Vec3f trans = moduleAccesser->getMotionModule().getTransNTranslate();
            Vec3f newPos(cliffPos.m_x + trans.m_z * lr, cliffPos.m_y + trans.m_y, pos.m_z);
            moduleAccesser->getPostureModule().setPos(&newPos);
            moduleAccesser->getStageObject().updateNodeSRT();
            moduleAccesser->getControllerModule().setRumble(0xd, 0, false, -1);
            b = true;
            break;
        }
        case Fighter::Status::Cliff_Attack:
        case Fighter::Status::Cliff_Climb:
        case Fighter::Status::Cliff_Escape:
        case Fighter::Status::Cliff_Jump1:
            b = true;
            break;
        case Fighter::Status::Cliff_Wait: {
            soDamageModule* damage = &moduleAccesser->getDamageModule();
            float damageMax = soValueAccesser::getConstantFloat(moduleAccesser, 0xc79, 0);
            if (damage->getDamage(0) < damageMax) {
                int frame = soValueAccesser::getConstantInt(moduleAccesser, 0x5a08, 0);
                moduleAccesser->getWorkManageModule().setInt(frame, 0x20000000);
            } else {
                int frame = soValueAccesser::getConstantInt(moduleAccesser, 0x5a09, 0);
                moduleAccesser->getWorkManageModule().setInt(frame, 0x20000000);
            }
            int xluFrame = soValueAccesser::getConstantInt(moduleAccesser, 0x5a0b, 0);
            moduleAccesser->getCollisionHitModule().setXluFrameGlobal(xluFrame, 0);
            b = true;
            break;
        }
        case Fighter::Status::Cliff_Jump2:
            a = false;
            break;
        }
        if (a == true) {
            moduleAccesser->getWorkManageModule().onFlag(0x12000002);
        }
        if (b == true) {
            moduleAccesser->getGroundModule().setShapeFlag((soGroundShapeImpl::ShapeFlagId)9, true, 0);
        }
    }
}

void ftStatusUniqProcessCliff::execStatus(soModuleAccesser* moduleAccesser) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
    case Fighter::Status::Cliff_Wait:
        float stickX = moduleAccesser->getControllerModule().getStickX();
        float stickY = moduleAccesser->getControllerModule().getStickY();
        float stickThreshold = soValueAccesser::getConstantFloat(moduleAccesser, 0xc7a, 0);
        if ((float)fabs(stickX) >= stickThreshold || (float)fabs(stickY) >= stickThreshold) {
            if (stickY >= soValueAccesser::getConstantFloat(moduleAccesser, 0xc42, 0)) {
                soControllerModule* controller = &moduleAccesser->getControllerModule();
                int flickFrames = soValueAccesser::getConstantInt(moduleAccesser, 0x59fb, 0);
                if (controller->getFlickY() < flickFrames) {
                    if (moduleAccesser->getWorkManageModule().isFlag(0x22000013) == true) {
                        moduleAccesser->getWorkManageModule().onFlag(0x22000014);
                    }
                    goto tail;
                }
            }
            if (moduleAccesser->getWorkManageModule().isFlag(0x22000013) == true) {
                float stickDir = moduleAccesser->getControllerModule().getStickDir();
                float dirThreshold = soValueAccesser::getConstantFloat(moduleAccesser, 0xc7b, 0);
                if (stickDir > dirThreshold) {
                    if (stickY >= soValueAccesser::getConstantFloat(moduleAccesser, 0xc42, 0)) {
                        moduleAccesser->getWorkManageModule().onFlag(0x22000010);
                    }
                } else if (stickDir > -dirThreshold
                           && stickX * moduleAccesser->getPostureModule().getLr() >= 0.0f) {
                    moduleAccesser->getWorkManageModule().onFlag(0x22000010);
                } else {
                    moduleAccesser->getWorkManageModule().onFlag(0x22000011);
                }
            }
        } else {
            moduleAccesser->getWorkManageModule().onFlag(0x22000013);
        }
tail:
        if (moduleAccesser->getWorkManageModule().getInt(0x20000000) > 0) {
            moduleAccesser->getWorkManageModule().decInt(0x20000000);
        }
        if (moduleAccesser->getWorkManageModule().getInt(0x20000000) <= 0) {
            moduleAccesser->getWorkManageModule().onFlag(0x22000012);
        }
        break;
    }
}

void ftStatusUniqProcessCliff::execFixPos(soModuleAccesser* moduleAccesser) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
    case Fighter::Status::Cliff_Wait:
        if (moduleAccesser->getGroundModule().isTouch(8, 0) == true) {
            moduleAccesser->getSituationModule().setKind(Situation_Ground, false);
            moduleAccesser->getStatusModule().changeStatusRequest(Fighter::Status::Wait, moduleAccesser);
        }
        break;
    case Fighter::Status::Cliff_Catch:
    case Fighter::Status::Cliff_Attack:
    case Fighter::Status::Cliff_Climb:
    case Fighter::Status::Cliff_Escape:
    case Fighter::Status::Cliff_Jump1: {
        ftKineticEnergyMotion* energy = (ftKineticEnergyMotion*)__dynamic_cast(
            moduleAccesser->getKineticModule().getEnergy(0), 0, __RTTI__21ftKineticEnergyMotion,
            __RTTI__15soKineticEnergy, 1);
        if (moduleAccesser->getGroundModule().isStCliff(0) == true) {
            bool ok = false;
            if (energy->m_motionMode == 0xb) {
                Vec3f speed = moduleAccesser->getMotionModule().getTransNTranslate();
                if (speed.m_z >= -0.03f && speed.m_y >= -0.03f) {
                    ok = true;
                }
            }
            if (ok == true) {
                energy->m_motionMode = 2;
                moduleAccesser->getGroundModule().setShapeFlag((soGroundShapeImpl::ShapeFlagId)9, false, 0);
                moduleAccesser->getSituationModule().setKind(Situation_Ground, false);
                moduleAccesser->getGroundModule().setCorrect(soGroundShapeImpl::Correct_Ground_Cliff_Stop, 0);
                moduleAccesser->getGroundModule().setStGroundForce(0);
                moduleAccesser->getGroundModule().leaveCliff(0);
                moduleAccesser->getWorkManageModule().onFlag(0x22000015);
            }
        } else if (moduleAccesser->getSituationModule().getKind() == Situation_Ground) {
            if ((u8)moduleAccesser->getGroundModule().getCorrect(0) == soGroundShapeImpl::Correct_Cliff) {
                energy->m_motionMode = 2;
                moduleAccesser->getGroundModule().setShapeFlag((soGroundShapeImpl::ShapeFlagId)9, false, 0);
                moduleAccesser->getGroundModule().setCorrect(soGroundShapeImpl::Correct_Ground_Cliff_Stop, 0);
                moduleAccesser->getGroundModule().leaveCliff(0);
                moduleAccesser->getWorkManageModule().onFlag(0x22000015);
            }
        } else if (moduleAccesser->getSituationModule().getKind() == Situation_Cliff) {
            moduleAccesser->getSituationModule().setKind(Situation_Air, false);
            moduleAccesser->getStatusModule().changeStatusRequest(Fighter::Status::Fall, moduleAccesser);
        }
        break;
    }
    }
}

void ftStatusUniqProcessCliff::exitStatus(soModuleAccesser* moduleAccesser, int nextStatus) {
    if (moduleAccesser->getWorkManageModule().isFlag(0x12000002) == true) {
        int frame = soValueAccesser::getConstantInt(moduleAccesser, 0x5a0a, 0);
        moduleAccesser->getWorkManageModule().setInt(frame, 0x10000002);
    }
    moduleAccesser->getWorkManageModule().offFlag(0x12000002);
    if (isLeaveCliff(nextStatus) == true) {
        moduleAccesser->getGroundModule().leaveCliff(0);
    }
}

bool ftStatusUniqProcessCliff::isLeaveCliff(int status) {
    switch (status) {
    case Fighter::Status::Cliff_Catch:
    case Fighter::Status::Cliff_Wait:
    case Fighter::Status::Cliff_Attack:
    case Fighter::Status::Cliff_Climb:
    case Fighter::Status::Cliff_Escape:
    case Fighter::Status::Cliff_Jump1:
        return false;
    }
    return true;
}

bool ftStatusUniqProcessCliff::isLeaveCliffStatus(int status) {
    switch (status) {
    case Fighter::Status::Cliff_Catch:
    case Fighter::Status::Cliff_Wait:
    case Fighter::Status::Cliff_Attack:
    case Fighter::Status::Cliff_Climb:
    case Fighter::Status::Cliff_Escape:
    case Fighter::Status::Cliff_Jump1:
        return false;
    }
    return true;
}
