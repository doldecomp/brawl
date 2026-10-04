#include <ft/ft_kinetic_energy_controller.h>
#include <math.h>
#include <so/so_kinetic_utility.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

ftKineticEnergyController::ftKineticEnergyController() : m_mode(-1), m_unk38(1.0f) { }

void ftKineticEnergyController::updateEnergy(soModuleAccesser* moduleAccesser) {
    Vec2f savedTarget;
    Vec2f::copy(savedTarget, m_speedTarget);
    float stickX = moduleAccesser->getControllerModule().getStickX();
    float stickY = moduleAccesser->getControllerModule().getStickY();
    float accelX = 0.0f;
    float addX = 0.0f;
    float addY = 0.0f;
    float accelY = m_accel.m_y;
    bool scaleTargetByStick = true;
    if (moduleAccesser->getWorkManageModule().getInt(0x10000038) > 0) {
        stickX = 0.0f;
    }
    if (0.0f != stickX) {
        addX = m_unk40;
    }
    if (0.0f != stickY) {
        addY = m_unk40;
    }
    switch (m_mode) {
    case 0:
    case 1:
    case 4:
    case 6:
    case 7:
    case 9:
    case 17:
    case 18:
        accelX = stickX * m_accelMul;
        if (stickX > 0.0f) {
            addX = addX;
        } else {
            addX = -addX;
        }
        accelX = accelX + addX;
        break;
    case 5: {
        float lr = moduleAccesser->getPostureModule().getLr();
        if (stickX * lr > 0.0f) {
            accelX = stickX * m_accelMul;
            if (stickX > 0.0f) {
                addX = addX;
            } else {
                addX = -addX;
            }
            accelX = accelX + addX;
        } else {
            m_speedTarget = Vec2f(0.0f, 0.0f);
        }
        break;
    }
    case 13:
        if (moduleAccesser->getWorkManageModule().isFlag(0x22000010) == true) {
            stickX = 0.0f;
        } else {
            float lr = moduleAccesser->getPostureModule().getLr();
            if (stickX * lr > 0.0f) {
                accelX = stickX * m_accelMul;
                if (stickX > 0.0f) {
                    addX = addX;
                } else {
                    addX = -addX;
                }
                accelX = accelX + addX;
                float mul = moduleAccesser->getWorkManageModule().getFloat(0x21000004);
                accelX = accelX * mul;
                m_speedTarget = Vec2f(savedTarget.m_x * mul, savedTarget.m_y);
            }
        }
        break;
    case 15:
        accelX = stickX * m_accelMul;
        if (stickX > 0.0f) {
            addX = addX;
        } else {
            addX = -addX;
        }
        accelX = accelX + addX;
        m_speedTarget = Vec2f((float)fabs(stickX * soValueAccesser::getConstantFloat(moduleAccesser, 0xc14, 0)), -1.0f);
        break;
    case 16: {
        accelX = stickX * m_accelMul;
        if (stickX > 0.0f) {
            addX = addX;
        } else {
            addX = -addX;
        }
        accelX = accelX + addX;
        float a = soValueAccesser::getConstantFloat(moduleAccesser, 0xd1f, 0);
        float b = soValueAccesser::getConstantFloat(moduleAccesser, 0xc14, 0);
        m_speedTarget = Vec2f((float)fabs(stickX * (b * a)), -1.0f);
        break;
    }
    case 3:
        if (moduleAccesser->getWorkManageModule().getInt(0x20000002) == 0) {
            accelX = stickX * m_accelMul;
            if (stickX > 0.0f) {
                addX = addX;
            } else {
                addX = -addX;
            }
            accelX = accelX + addX;
        }
        break;
    case 10:
        accelX = stickX * m_accelMul;
        if (stickX > 0.0f) {
            addX = addX;
        } else {
            addX = -addX;
        }
        accelX = accelX + addX;
        accelX = accelX * soValueAccesser::getConstantFloat(moduleAccesser, 0xbe0, 0);
        break;
    case 8:
        accelX = stickX * m_accelMul;
        if (stickX > 0.0f) {
            addX = addX;
        } else {
            addX = -addX;
        }
        accelX = accelX + addX;
        if (!(accelX * m_unk38 < 0.0f)) {
            accelX = 0.0f;
            m_speedTarget = Vec2f(0.0f, 0.0f);
            scaleTargetByStick = false;
        }
        break;
    case 11:
    case 12:
        accelX = stickX * m_accelMul;
        if (stickX > 0.0f) {
            addX = addX;
        } else {
            addX = -addX;
        }
        accelX = accelX + addX;
        accelY = stickY * m_unk44;
        if (stickY > 0.0f) {
            addY = addY;
        } else {
            addY = -addY;
        }
        accelY = accelY + addY;
        {
            Vec2f t;
            Vec2f::copy(t, m_speedTarget);
            t.m_y = (float)fabs(stickY) * t.m_y;
            m_speedTarget = t;
        }
        break;
    case 2:
    case 14:
        break;
    }
    m_accel = Vec2f(accelX, accelY);
    if (scaleTargetByStick) {
        m_speedTarget = Vec2f(m_speedTarget.m_x * (float)fabs(stickX), m_speedTarget.m_y);
    }
    soKineticEnergyNormal::updateEnergy(moduleAccesser);
    m_speedTarget.m_x = savedTarget.m_x;
    m_speedTarget.m_y = savedTarget.m_y;
}

void ftKineticEnergyController::resetEnergy(int mode, Vec2f* speed, Vec3f*, soModuleAccesser* moduleAccesser) {
    clearSpeed();
    float sx = speed->m_x;
    float sy = speed->m_y;
    m_accel = Vec2f(0.0f, 0.0f);
    m_speedTarget = Vec2f(0.0f, 0.0f);
    m_brake = Vec2f(0.0f, 0.0f);
    m_speedLimit = Vec2f(-1.0f, -1.0f);
    m_speed.m_x = sx;
    m_speed.m_y = sy;
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
            v = soKineticUtility::limitSpeed(&v, &Vec2f(soValueAccesser::getConstantFloat(moduleAccesser, 0xbd5, 0), -1.0f));
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
            v = soKineticUtility::limitSpeed(&v, &Vec2f(a * param[3], -1.0f));
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
        float sx = getSpeed().m_x;
        float x;
        if (sx * lr >= 0.0f) {
            x = lr * c;
        } else {
            x = sx + lr * c;
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
        float x = getSpeed().m_x;
        if (mode == 7) {
            float c = soValueAccesser::getConstantFloat(moduleAccesser, 0xbff, 0);
            if (x * lr <= 0.0f) {
                x = lr * -c;
            } else {
                x += lr * -c;
            }
        } else {
            float c = soValueAccesser::getConstantFloat(moduleAccesser, 0xbfe, 0);
            if (x * lr >= 0.0f) {
                x = lr * c;
            } else {
                x += lr * c;
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
        float sx = getSpeed().m_x;
        float c = soValueAccesser::getConstantFloat(moduleAccesser, 0xfa7, 0);
        m_speed = Vec2f(sx * c, 0.0f);
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
        float targetX = scale * soValueAccesser::getConstantFloat(moduleAccesser, 0xbf5, 0);
        scale = moduleAccesser->getPostureModule().getScale();
        float limitX = scale * soValueAccesser::getConstantFloat(moduleAccesser, 0xbc2, 0);
        float a = soValueAccesser::getConstantFloat(moduleAccesser, 0xbbc, 0);
        float b = soValueAccesser::getConstantFloat(moduleAccesser, 0xc38, 0);
        m_brake = Vec2f(a * b, 0.0f);
        m_speedLimit = Vec2f(limitX, 0.0f);
        m_speedTarget = Vec2f(targetX, -1.0f);
        scale = moduleAccesser->getPostureModule().getScale();
        m_accelMul = scale * soValueAccesser::getConstantFloat(moduleAccesser, 0xbf3, 0);
        scale = moduleAccesser->getPostureModule().getScale();
        m_unk40 = scale * soValueAccesser::getConstantFloat(moduleAccesser, 0xbf4, 0);
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
        m_speed = soKineticUtility::projectionGroundSpeed(&getSpeed(), moduleAccesser);
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
