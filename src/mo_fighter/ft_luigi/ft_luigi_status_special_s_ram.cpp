#include <ft/luigi/ft_luigi_status_special_s.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <so/work/so_work_manage_module_impl.h>
#include <so/ground/so_ground_module_impl.h>
#include <so/collision/so_collision_attack_module_impl.h>
#include <so/kinetic/so_kinetic_module_impl.h>
#include <so/status/so_status_module_impl.h>
#include <mt/mt_prng.h>

void ftLuigiStatusUniqProcessSpecialSRam::initStatus(soModuleAccesser* moduleAccesser) {
    moduleAccesser->getGroundModule().setTestCollStopStatus(true, 0);
}

void ftLuigiStatusUniqProcessSpecialSRam::execFixPos(soModuleAccesser* moduleAccesser) {
    soGroundModule& ground = moduleAccesser->getGroundModule();
    grCollStatus::TouchMask touchFlags = ground.getTouchFlag(0);
    if ((touchFlags & 0x6) != 0) {
        int status = 0x119;
        if (ground.isAttachable(touchFlags, 0)) {
            Vec3f speed = moduleAccesser->getKineticModule().getSumSpeed3f(
                soKineticEnergy::AttributeFlag(soKineticEnergy::ATTRIBUTE_MASK_ALL));
            float threshold = soValueAccesser::getConstantFloat(moduleAccesser, 0xFBB, 0);
            if (__fabsf(speed.m_x) >= threshold) {
                float chance = soValueAccesser::getConstantFloat(moduleAccesser, 0xFBC, 0);
                if (randf() < chance) {
                    float lr = moduleAccesser->getPostureModule().getLr();
                    if ((touchFlags & 0x2) != 0) {
                        if (lr == -1.0f) {
                            status = 0x11A;
                        }
                    } else if (lr == 1.0f) {
                        status = 0x11A;
                    }
                }
            }
        }
        moduleAccesser->getStatusModule().changeStatusRequest(status, moduleAccesser);
    } else {
        soWorkManageModule& work = moduleAccesser->getWorkManageModule();
        if (!work.isFlag(0x22000012) && !work.isFlag(0x22000015) &&
            !moduleAccesser->getCollisionAttackModule().isAttack(0, false)) {
            float scale = soValueAccesser::getConstantFloat(moduleAccesser, 0xFAC, 0);
            int count = work.getInt(0x20000000);
            float scaledCount = count * scale;
            float offset = soValueAccesser::getConstantFloat(moduleAccesser, 0xFAB, 0);
            work.setInt((int)(offset + scaledCount), 0x20000000);
            work.offFlag(0x22000015);
        }
    }
}

ftLuigiStatusUniqProcessSpecialSRam g_ftLuigiStatusUniqProcessSpecialSRam;
