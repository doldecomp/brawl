#include <ft/ft_kinetic_energy.h>
#include <ft/ft_manager.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

// Marth Down-B (counter) status process. The class that owns these is not modelled yet,
// so they are plain functions named after their symbols (first argument is `this`).
// TODO: find the real home of this helper (sora_melee)
void ftKineticEnergyDisableAndClear(int index, soModuleAccesser* moduleAccesser);

FT_DEFINE_GET_SUM_SPEED(getSumSpeedInit)
FT_DEFINE_GET_SUM_SPEED(getSumSpeedExec)

extern "C" {

void fn_106_C390(u8* obj, const float* src);
void fn_106_C674();
void fn_106_C98C(const void** obj);

extern const void* lbl_106_data_5600[];

void fn_106_C390(u8* obj, const float* src) {
    *(float*) (obj + 32) = src[0];
    *(float*) (obj + 36) = src[1];
}

void fn_106_C674() {}

void fn_106_C98C(const void** obj) {
    *obj = lbl_106_data_5600;
}

void fn_106_BFF0(void* self, soModuleAccesser* moduleAccesser) {
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*moduleAccesser->getKineticModule().getEnergy(3));
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*moduleAccesser->getKineticModule().getEnergy(1));
    float speedX = getSumSpeedInit(moduleAccesser).m_x;
        switch (moduleAccesser->getStatusModule().getStatusKind()) {
        case 0x115:
            if (moduleAccesser->getSituationModule().getKind() == 2) {
                speedX *= soValueAccesser::getConstantFloat(moduleAccesser, 0xfb0, 0);
                stop.resetEnergy(6, &Vec2f(speedX, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
                { Vec2f brake(soValueAccesser::getConstantFloat(moduleAccesser, 0xfb1, 0), 0.0f); fn_106_C390((u8*)&stop, &brake.m_x); }
                stop.enable();
                gravity.resetEnergy(0, &Vec2f(0.0f, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
                gravity.m_gravity = -soValueAccesser::getConstantFloat(moduleAccesser, 0xfb2, 0);
                gravity.m_fallSpeedMax = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb3, 0);
                gravity.enable();
                ftKineticEnergyDisableAndClear(2, moduleAccesser);
                moduleAccesser->getWorkManageModule().setInt(2, 0x20000000);
            } else {
                moduleAccesser->getWorkManageModule().setInt(0, 0x20000000);
            }
            break;
        case 0x11d: {
            float work = moduleAccesser->getWorkManageModule().getFloat(0x21000004);
            float a = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb4, 0);
            float max = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb7, 0);
            if (*(u8*)((u8*)g_ftManager + 0x68) == 1) {
                a = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb5, 0);
                max = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb8, 0);
            }
            float value = work * a;
            if (value < soValueAccesser::getConstantFloat(moduleAccesser, 0xfb6, 0)) {
                value = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb6, 0);
            }
            if (value > max) {
                value = max;
            }
            moduleAccesser->getWorkManageModule().setFloat(value, 0x21000004);
            break;
        }
    }
}

void fn_106_C890(void* self, soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000012)) {
        moduleAccesser->getCollisionShieldModule().setStatus(0, 0, 1);
    }
}

void fn_106_C3A4(void* self, soModuleAccesser* moduleAccesser) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
        case 0x115: {
            soWorkManageModule& work = moduleAccesser->getWorkManageModule();
            soSituationModule& situation = moduleAccesser->getSituationModule();
            if (situation.getKind() != work.getInt(0x20000000)) {
                ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*moduleAccesser->getKineticModule().getEnergy(3));
                ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*moduleAccesser->getKineticModule().getEnergy(1));
                const Vec2f& sumSpeed = getSumSpeedExec(moduleAccesser);
                float speedX = sumSpeed.m_x;
                float speedY = sumSpeed.m_y;
                if (situation.getKind() == 2) {
                    stop.resetEnergy(6, &Vec2f(speedX, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
                    { Vec2f brake(soValueAccesser::getConstantFloat(moduleAccesser, 0xfb1, 0), 0.0f); fn_106_C390((u8*)&stop, &brake.m_x); }
                    stop.enable();
                    gravity.resetEnergy(0, &Vec2f(0.0f, speedY), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
                    gravity.m_gravity = -soValueAccesser::getConstantFloat(moduleAccesser, 0xfb2, 0);
                    gravity.m_fallSpeedMax = soValueAccesser::getConstantFloat(moduleAccesser, 0xfb3, 0);
                    gravity.enable();
                    ftKineticEnergyDisableAndClear(2, moduleAccesser);
                    moduleAccesser->getWorkManageModule().setInt(2, 0x20000000);
                } else {
                    moduleAccesser->getWorkManageModule().setInt(0, 0x20000000);
                }
            }
            break;
        }
        case 0x11d:
            break;
    }
}

void fn_106_C678(void* self, soModuleAccesser* moduleAccesser) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
        case 0x115:
            if (!moduleAccesser->getWorkManageModule().isFlag(0x22000012)) {
                if (moduleAccesser->getWorkManageModule().isFlag(0x22000011)) {
                    moduleAccesser->getCollisionShieldModule().setStatus(0, 1, 1);
                    moduleAccesser->getWorkManageModule().onFlag(0x22000012);
                }
            } else if (!moduleAccesser->getWorkManageModule().isFlag(0x22000011)) {
                moduleAccesser->getCollisionShieldModule().setStatus(0, 0, 1);
                moduleAccesser->getWorkManageModule().offFlag(0x22000012);
            }
            break;
        case 0x11d: {
            soCollisionAttackModule& attack = moduleAccesser->getCollisionAttackModule();
            float power = moduleAccesser->getWorkManageModule().getFloat(0x21000004);
            if (!(power <= 0.0f)) {
                for (int i = 0; i < (int)attack.getPartSize(); i++) {
                    if (attack.isAttack(i, false)) {
                        attack.setPower(i, (int)power, false);
                    }
                }
            }
            break;
        }
    }
}

}
