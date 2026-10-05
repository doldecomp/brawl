#include <mt/mt_vector.h>
#include <so/so_kinetic_energy_normal.h>
#include <so/so_kinetic_utility.h>
#include <so/so_module_accesser.h>
#include <types.h>

void soKineticEnergyNormal::updateEnergy(soModuleAccesser* moduleAccesser) {
    if (m_accel.lengthSq() != 0.0f || m_speed.lengthSq() != 0.0f) {
        Vec2f accel;
        Vec2f::copy(accel, m_accel);
        Vec2f brake;
        Vec2f::copy(brake, m_brake);
        if (moduleAccesser->getSituationModule().getKind() == Situation_Ground) {
            if (m_unk30 == true || (m_considerGroundFriction == true && m_unk32 == true)) {
                if (moduleAccesser->getGroundModule().isTouch(8, 0)) {
                    if (m_considerGroundFriction == true && m_unk32 == true) {
                        if (accel.lengthSq() != 0.0f || brake.lengthSq() != 0.0f) {
                            float friction = moduleAccesser->getGroundModule().getDownFriction(0);
                            if (friction > 1.0f) {
                                brake.m_x *= friction;
                                brake.m_y *= friction;
                            } else if (friction < 1.0f) {
                                accel.m_x *= friction;
                                accel.m_y *= friction;
                                brake.m_x *= friction;
                                brake.m_y *= friction;
                            }
                        }
                    }
                    if (m_unk30 == true) {
                        if (accel.lengthSq() != 0.0f) {
                            Vec2f normal;
                            Vec2f::copy(normal, moduleAccesser->getGroundModule().getTouchNormal(8, 0));
                            accel = soKineticUtility::projectionNormalFollow(&accel, &normal);
                        }
                    }
                }
            }
        }
        accel = soKineticUtility::brakeSpeed(&m_speed, &accel, &m_speedTarget, &brake);
        if (accel.lengthSq() != 0.0f) {
            m_speed.m_x += accel.m_x;
            m_speed.m_y += accel.m_y;
        }
        m_speed = soKineticUtility::limitSpeed(&m_speed, &m_speedLimit);
    }
}

void soKineticEnergyNormal::mulSpeed(Vec3f* speed) {
    Vec2f mul = *speed->xy();
    m_speed.m_x *= mul.m_x;
    m_speed.m_y *= mul.m_y;
}

void soKineticEnergyNormal::mulAccel(Vec3f* accel) {
    Vec2f mul = *accel->xy();
    m_accel.m_x *= mul.m_x;
    m_accel.m_y *= mul.m_y;
}

// Reflects v about the normal n (out = v - 2 n (n . v)).
static inline void reflectVec(Vec2f& out, const Vec2f& v, const Vec2f& n) {
    out = v - n * 2.0f * (n.m_x * v.m_x + n.m_y * v.m_y);
}

void soKineticEnergyNormal::reflectSpeed(Vec3f* normal) {
    Vec2f n = *normal->xy();
    reflectVec(m_speed, m_speed, n);
}

void soKineticEnergyNormal::reflectAccel(Vec3f* normal) {
    Vec2f n = *normal->xy();
    reflectVec(m_accel, m_accel, n);
}

void soKineticEnergyNormal::clearRotSpeed() { }

void soKineticEnergyNormal::clearSpeed() {
    m_speed = Vec2f(0.0f, 0.0f);
}

void soKineticEnergyNormal::resetEnergy(int, Vec2f* speed, Vec3f*, soModuleAccesser*) {
    // MATCH-ONLY: the extra copy of x forces the original load order (x before y).
    float y;
    float tmp = speed->m_x;
    y = speed->m_y;
    float x = tmp;
    m_speed.m_x = x;
    m_speed.m_y = y;
}

void soKineticEnergyNormal::init() {
    Vec2f zero(0.0f, 0.0f);
    m_brake = zero;
    m_accel = zero;
    m_speed = zero;
    Vec2f negOne(-1.0f, -1.0f);
    m_speedLimit = negOne;
    m_speedTarget = negOne;
    m_considerGroundFriction = false;
    m_unk30 = false;
    m_unk32 = true;
}

void soKineticEnergyNormal::offConsiderGroundFriction() {
    m_considerGroundFriction = false;
}

void soKineticEnergyNormal::onConsiderGroundFriction() {
    m_considerGroundFriction = true;
}

Vec3f soKineticEnergyNormal::getRotation() {
    return Vec3f(0.0f, 0.0f, 0.0f);
}

Vec2f soKineticEnergyNormal::getSpeed() {
    return m_speed;
}


