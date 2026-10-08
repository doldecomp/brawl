#include <ft/builder/ft_dol_array_list.h>
#include <ft/luigi/ft_luigi_kinetic_transactor.h>
#include <ft/builder/ft_builder_kinetic.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_kinetic_utility.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>

void ftLuigiKineticTransactor::changeKinetic(int mode, void* pools, soModuleAccesser* moduleAccesser) {
    if (mode <= 0x63) {
        ftKineticTransactor::changeKinetic(mode, pools, moduleAccesser);
        return;
    }

    Vec2f speed = ftKineticTransactHelper::preHelpProcess(moduleAccesser, 1, 1);
    bool result = false;
    switch (mode) {
    case 0x64:
        ftLuigiKineticTransactor::changeKineticSub(&result, pools, &speed, moduleAccesser);
        break;
    case 0x65:
        ftLuigiKineticTransactor::changeKineticSub1(&result, pools, &speed, moduleAccesser);
        break;
    case 0x66:
        ftLuigiKineticTransactor::changeKineticSub2(&result, pools, &speed, moduleAccesser);
        break;
    case 0x67:
        ftLuigiKineticTransactor::changeKineticSub3(&result, pools, &speed, moduleAccesser);
        break;
    case 0x68:
        ftLuigiKineticTransactor::changeKineticSub4(&result, pools, &speed, moduleAccesser);
        break;
    case 0x69:
        ftLuigiKineticTransactor::changeKineticSub5(&result, pools, &speed, moduleAccesser);
        break;
    case 0x6A:
        ftLuigiKineticTransactor::changeKineticSub6(&result, pools, &speed, moduleAccesser);
        break;
    case 0x6B:
        ftLuigiKineticTransactor::changeKineticSub7(&result, pools, &speed, moduleAccesser);
        break;
    case 0x6C:
    case 0x6D:
        result = false;
        break;
    default:
        return;
    }
    ftKineticTransactor::enableOutsideEnergy(moduleAccesser);
}

void ftLuigiKineticTransactor::changeKineticSub(bool*, void*, Vec2f*, soModuleAccesser* moduleAccesser) {
    ftKineticTransactor::changeKineticImpl(6);
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(
        *moduleAccesser->getKineticModule().getEnergy(3));
    if (!moduleAccesser->getWorkManageModule().isFlag(0x22000010)) {
        Vec2f speed = stop.getSpeed();
        speed.m_x /= soValueAccesser::getConstantFloat(moduleAccesser, 0xFAD, 0);
        stop.m_speed = speed;
    }
    stop.m_brake = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xFAE, 0), 0.0f);
}

void ftLuigiKineticTransactor::changeKineticSub1(bool*, void*, Vec2f*, soModuleAccesser* moduleAccesser) {
    ftKineticTransactor::changeKineticImpl(13);
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(
        *moduleAccesser->getKineticModule().getEnergy(3));
    if (!moduleAccesser->getWorkManageModule().isFlag(0x22000010)) {
        Vec2f speed = stop.getSpeed();
        speed.m_x /= soValueAccesser::getConstantFloat(moduleAccesser, 0xFAD, 0);
        stop.m_speed = speed;
    }
    stop.m_brake = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xFAE, 0), 0.0f);
}

void ftLuigiKineticTransactor::changeKineticSub2(bool*, void*, Vec2f* speed, soModuleAccesser* moduleAccesser) {
    ftKineticTransactor::changeKineticImpl(10);
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(
        *moduleAccesser->getKineticModule().getEnergy(3));
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(
        *moduleAccesser->getKineticModule().getEnergy(1));

    float stopSpeed;
    float gravitySpeed;
    if (moduleAccesser->getWorkManageModule().isFlag(0x22000012)) {
        stopSpeed = soValueAccesser::getConstantFloat(moduleAccesser, 0xFB9, 0);
        gravitySpeed = soValueAccesser::getConstantFloat(moduleAccesser, 0xFBA, 0);
    } else {
        int count = moduleAccesser->getWorkManageModule().getInt(0x20000000);
        stopSpeed = count * soValueAccesser::getConstantFloat(moduleAccesser, 0xFB1, 0) +
                    soValueAccesser::getConstantFloat(moduleAccesser, 0xFB0, 0);
        gravitySpeed = count * soValueAccesser::getConstantFloat(moduleAccesser, 0xFB3, 0) +
                       soValueAccesser::getConstantFloat(moduleAccesser, 0xFB2, 0);
    }

    stop.m_speed = Vec2f(stopSpeed * moduleAccesser->getPostureModule().getLr(), 0.0f);
    stop.m_brake = Vec2f(0.0f, 0.0f);
    gravity.m_speedY = gravitySpeed;
    gravity.m_gravity = -soValueAccesser::getConstantFloat(moduleAccesser, 0xFB4, 0);
    gravity.m_fallSpeedMax = soValueAccesser::getConstantFloat(moduleAccesser, 0xFB5, 0);
}

void ftLuigiKineticTransactor::changeKineticSub3(bool*, void*, Vec2f*, soModuleAccesser* moduleAccesser) {
    ftKineticTransactor::changeKineticImpl(6);
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(
        *moduleAccesser->getKineticModule().getEnergy(3));
    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    if (!work.isFlag(0x22000014) && work.isFlag(0x22000013)) {
        stop.m_speed = Vec2f(0.0f, 0.0f);
    }
    stop.m_brake = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xFB7, 0), 0.0f);
}

void ftLuigiKineticTransactor::changeKineticSub4(bool*, void*, Vec2f*, soModuleAccesser* moduleAccesser) {
    ftKineticTransactor::changeKineticImpl(10);
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(
        *moduleAccesser->getKineticModule().getEnergy(3));
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(
        *moduleAccesser->getKineticModule().getEnergy(1));
    stop.m_brake = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xFB7, 0), 0.0f);
    gravity.m_gravity = -soValueAccesser::getConstantFloat(moduleAccesser, 0xFB8, 0);

    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    if (!work.isFlag(0x22000014) && work.isFlag(0x22000013)) {
        stop.m_speed = Vec2f(0.0f, 0.0f);
        Vec2f gravitySpeed = gravity.getSpeed();
        if (gravitySpeed.m_y > 0.0f) {
            gravity.m_speedY = 0.0f;
        }
    }
}

void ftLuigiKineticTransactor::changeKineticSub5(bool*, void*, Vec2f* speed, soModuleAccesser* moduleAccesser) {
    ftKineticEnergyController& controller = dynamic_cast<ftKineticEnergyController&>(
        *moduleAccesser->getKineticModule().getEnergy(2));
    Vec3f rotation(0.0f, 0.0f, 0.0f);
    Vec2f initialSpeed = *speed;
    controller.resetEnergy(0x11, &initialSpeed, &rotation, moduleAccesser);
    controller.m_accelMul = soValueAccesser::getConstantFloat(moduleAccesser, 0xFBF, 0);
    controller.m_speedTarget = Vec2f(0.0f, 0.0f);
    controller.m_brake = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xBBC, 0), 0.0f);
    controller.m_speedLimit = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xFBE, 0), 0.0f);
    controller.enable();
}

void ftLuigiKineticTransactor::changeKineticSub6(bool*, void*, Vec2f* speed, soModuleAccesser* moduleAccesser) {
    ftKineticEnergyController& controller = dynamic_cast<ftKineticEnergyController&>(
        *moduleAccesser->getKineticModule().getEnergy(2));
    Vec3f rotation(0.0f, 0.0f, 0.0f);
    Vec2f initialSpeed = *speed;
    controller.resetEnergy(0x12, &initialSpeed, &rotation, moduleAccesser);
    controller.m_accelMul = soValueAccesser::getConstantFloat(moduleAccesser, 0xFC4, 0);
    controller.m_speedTarget = Vec2f(0.0f, 0.0f);
    controller.m_brake = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xBD6, 0), 0.0f);
    controller.m_speedLimit = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xFC3, 0), 0.0f);
    controller.enable();

    Vec2f gravitySpeed(0.0f, initialSpeed.m_y);
    soKineticUtility::resetEnableEnergy(1, moduleAccesser, 0, &gravitySpeed, &rotation);
}

void ftLuigiKineticTransactor::changeKineticSub7(bool*, void*, Vec2f*, soModuleAccesser* moduleAccesser) {
    ftKineticTransactor::changeKineticImpl(10);
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(
        *moduleAccesser->getKineticModule().getEnergy(1));
    gravity.m_speedY = 0.0f;
    gravity.m_gravity = -soValueAccesser::getConstantFloat(moduleAccesser, 0xFC5, 0);
    gravity.m_fallSpeedMax = soValueAccesser::getConstantFloat(moduleAccesser, 0xFC6, 0);
}

void ftLuigiKineticTransactor::updateEnergy(ftKineticEnergyMotion* energy, soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getKineticModule().getKineticType() == 0x66 &&
        moduleAccesser->getWorkManageModule().isFlag(0x22000014)) {
        energy->m_brake = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xFB7, 0), 0.0f);
    }
    energy->updateEnergy(moduleAccesser);
}

void ftLuigiKineticTransactor::updateEnergy(ftKineticEnergyController* energy, soModuleAccesser* moduleAccesser) {
    int kineticType = moduleAccesser->getKineticModule().getKineticType();
    if (kineticType == 0x6A) {
        float addSpeedY = moduleAccesser->getWorkManageModule().getFloat(0x21000005);
        if (addSpeedY > 0.0f) {
            Vec2f speed = energy->getSpeed();
            speed.m_y += addSpeedY;
            float speedLimit = soValueAccesser::getConstantFloat(moduleAccesser, 0xFC2, 0);
            if (speed.m_y > speedLimit) {
                speed.m_y = soValueAccesser::getConstantFloat(moduleAccesser, 0xFC2, 0);
            }
            energy->m_speed.m_y = speed.m_y;
        }
    } else if (kineticType == 0x66 &&
               moduleAccesser->getWorkManageModule().isFlag(0x22000014)) {
        energy->m_accel.m_x = -soValueAccesser::getConstantFloat(moduleAccesser, 0xFB8, 0);
    }
    energy->updateEnergy(moduleAccesser);
}
