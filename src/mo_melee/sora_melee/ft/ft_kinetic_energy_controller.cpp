#include <ft/ft_kinetic_energy_controller.h>
#include <so/so_kinetic_utility.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

ftKineticEnergyController::ftKineticEnergyController() : m_mode(-1), m_unk38(1.0f) { }

void ftKineticEnergyController::updateEnergy(soModuleAccesser* moduleAccesser) {
}

void ftKineticEnergyController::resetEnergy(int mode, Vec2f* speed, Vec3f*, soModuleAccesser* moduleAccesser) {
    clearSpeed();
    m_accel = Vec2f(0.0f, 0.0f);
    m_speedTarget = Vec2f(0.0f, 0.0f);
    m_brake = Vec2f(0.0f, 0.0f);
    m_speedLimit = Vec2f(-1.0f, -1.0f);
    m_speed = *speed;
    m_mode = mode;
    m_unk38 = moduleAccesser->getPostureModule().getLr();
    m_unk40 = 0.0f;
    m_accelMul = 0.0f;
    m_unk48 = 0.0f;
    m_unk44 = 0.0f;
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
        if (mode != 1) {
            Vec2f v(getSpeed().m_y + getSpeed().m_x, 0.0f);
            Vec2f limit(soValueAccesser::getConstantFloat(moduleAccesser, 0xbd5, 0), -1.0f);
            v = soKineticUtility::limitSpeed(&v, &limit);
            m_speed = v;
        }
        if (mode == 2) {
            float a = soValueAccesser::getConstantFloat(moduleAccesser, 0xc96, 0);
            float b = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd5, 0);
            m_speedTarget = Vec2f(b * a, -1.0f);
        } else {
            m_speedTarget = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbd5, 0), -1.0f);
        }
        m_brake = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbd6, 0), 0.0f);
        m_speedLimit = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbd8, 0), 0.0f);
        m_accelMul = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd3, 0);
        m_unk40 = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd4, 0);
        break;
    case 4: {
        float* param = (float*)soValueAccesser::getConstantIndefinite(moduleAccesser, 0xa80a, 0);
        if (param != 0) {
            float a = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd5, 0);
            Vec2f v(getSpeed().m_y + getSpeed().m_x, 0.0f);
            Vec2f limit(a * param[3], -1.0f);
            v = soKineticUtility::limitSpeed(&v, &limit);
            m_speed = v;
            m_speedTarget = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbd5, 0), -1.0f);
            m_brake = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbd6, 0), 0.0f);
            m_speedLimit = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbd8, 0), 0.0f);
            m_accelMul = param[2] * soValueAccesser::getConstantFloat(moduleAccesser, 0xbd3, 0);
            m_unk40 = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd4, 0);
        }
        break;
    }
    case 10: {
        m_speedTarget = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbbb, 0), -1.0f);
        m_speedLimit = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbc2, 0), 0.0f);
        float a = soValueAccesser::getConstantFloat(moduleAccesser, 0xbbc, 0);
        float b = soValueAccesser::getConstantFloat(moduleAccesser, 0xc38, 0);
        m_brake = Vec2f(a * b, 0.0f);
        m_accelMul = soValueAccesser::getConstantFloat(moduleAccesser, 0xbb9, 0);
        m_unk40 = soValueAccesser::getConstantFloat(moduleAccesser, 0xbba, 0);
        break;
    }
    case 5:
    case 8: {
        float lr = moduleAccesser->getPostureModule().getLr();
        float c = soValueAccesser::getConstantFloat(moduleAccesser, 0xbbd, 0);
        Vec2f cur = getSpeed();
        float x;
        if (cur.m_x * lr >= 0.0f) {
            x = lr * c;
        } else {
            x = cur.m_x + lr * c;
        }
        m_speed = Vec2f(x, 0.0f);
        m_speedTarget = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbc0, 0), -1.0f);
        m_speedLimit = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbc2, 0), 0.0f);
        float a = soValueAccesser::getConstantFloat(moduleAccesser, 0xbbc, 0);
        float b = soValueAccesser::getConstantFloat(moduleAccesser, 0xc38, 0);
        m_brake = Vec2f(a * b, 0.0f);
        m_accelMul = soValueAccesser::getConstantFloat(moduleAccesser, 0xbbe, 0);
        m_unk40 = soValueAccesser::getConstantFloat(moduleAccesser, 0xbbf, 0);
        break;
    }
    case 6:
    case 7: {
        float lr = moduleAccesser->getPostureModule().getLr();
        Vec2f cur = getSpeed();
        float x = cur.m_x;
        if (mode == 7) {
            float c = soValueAccesser::getConstantFloat(moduleAccesser, 0xbff, 0);
            if (x * lr <= 0.0f) {
                x = lr * -c;
            } else {
                x = x + lr * -c;
            }
        } else {
            float c = soValueAccesser::getConstantFloat(moduleAccesser, 0xbfe, 0);
            if (x * lr >= 0.0f) {
                x = lr * c;
            } else {
                x = x + lr * c;
            }
        }
        m_speed = Vec2f(x, 0.0f);
        m_speedTarget = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbc0, 0), -1.0f);
        m_speedLimit = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbc2, 0), 0.0f);
        float a = soValueAccesser::getConstantFloat(moduleAccesser, 0xbbc, 0);
        float b = soValueAccesser::getConstantFloat(moduleAccesser, 0xc38, 0);
        m_brake = Vec2f(a * b, 0.0f);
        m_accelMul = 0.0f;
        m_unk40 = 0.0f;
        break;
    }
    case 11: {
        float c;
        c = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd5, 0);
        m_speedTarget = Vec2f(c, c);
        c = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd6, 0);
        m_brake = Vec2f(c, c);
        c = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd8, 0);
        m_speedLimit = Vec2f(c, c);
        m_speed = Vec2f(0.0f, 0.0f);
        m_accelMul = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd3, 0);
        m_unk40 = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd4, 0);
        m_unk44 = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd3, 0);
        m_unk48 = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd4, 0);
        break;
    }
    case 12:
        m_speed = Vec2f(0.0f, 0.0f);
        m_speedTarget = Vec2f(2.5f, 2.5f);
        m_brake = Vec2f(0.4f, 0.4f);
        m_speedLimit = Vec2f(3.0f, 3.0f);
        m_accelMul = 0.2f;
        m_unk40 = 0.2f;
        m_unk44 = 0.2f;
        m_unk48 = 0.2f;
        break;
    case 9: {
        Vec2f cur = getSpeed();
        float c = soValueAccesser::getConstantFloat(moduleAccesser, 0xfa7, 0);
        m_speed = Vec2f(cur.m_x * c, 0.0f);
        float a = soValueAccesser::getConstantFloat(moduleAccesser, 0xfa9, 0);
        float b = soValueAccesser::getConstantFloat(moduleAccesser, 0xbd5, 0);
        m_speedTarget = Vec2f(b * a, -1.0f);
        m_brake = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbd6, 0), 0.0f);
        m_speedLimit = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbd8, 0), 0.0f);
        m_accelMul = soValueAccesser::getConstantFloat(moduleAccesser, 0xfa8, 0);
        m_unk40 = 0.0f;
        break;
    }
    case 13: {
        float scale = moduleAccesser->getPostureModule().getScale();
        float targetX = soValueAccesser::getConstantFloat(moduleAccesser, 0xbf5, 0) * scale;
        scale = moduleAccesser->getPostureModule().getScale();
        float limitX = soValueAccesser::getConstantFloat(moduleAccesser, 0xbc2, 0) * scale;
        float a = soValueAccesser::getConstantFloat(moduleAccesser, 0xbbc, 0);
        float b = soValueAccesser::getConstantFloat(moduleAccesser, 0xc38, 0);
        m_brake = Vec2f(a * b, 0.0f);
        m_speedLimit = Vec2f(limitX, 0.0f);
        m_speedTarget = Vec2f(targetX, -1.0f);
        scale = moduleAccesser->getPostureModule().getScale();
        m_accelMul = soValueAccesser::getConstantFloat(moduleAccesser, 0xbf3, 0) * scale;
        scale = moduleAccesser->getPostureModule().getScale();
        m_unk40 = soValueAccesser::getConstantFloat(moduleAccesser, 0xbf4, 0) * scale;
        break;
    }
    case 15:
        m_brake = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xc15, 0), 0.0f);
        m_accelMul = soValueAccesser::getConstantFloat(moduleAccesser, 0xc13, 0);
        m_unk40 = 0.0f;
        break;
    case 16: {
        m_brake = Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xc15, 0), 0.0f);
        float a = soValueAccesser::getConstantFloat(moduleAccesser, 0xd1f, 0);
        float b = soValueAccesser::getConstantFloat(moduleAccesser, 0xc13, 0);
        m_unk40 = 0.0f;
        m_accelMul = b * a;
        break;
    }
    case 17: {
        Vec2f cur = getSpeed();
        m_speed = soKineticUtility::projectionGroundSpeed(&cur, moduleAccesser);
        break;
    }
    case 14:
    case 18:
        break;
    }
}

void ftKineticEnergyController::mulXSpeedMax(float mul) {
    Vec2f v;
    Vec2f::copy(v, m_speedTarget);
    v.m_x *= mul;
    m_speedTarget = v;
}

void ftKineticEnergyController::mulXAccelMul(float mul) {
    m_accelMul *= mul;
}

ftKineticEnergyController::~ftKineticEnergyController() { }
