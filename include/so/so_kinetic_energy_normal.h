#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <so/kinetic/so_kinetic_energy.h>
#include <types.h>

class soModuleAccesser;

// Basic 2D speed/acceleration energy. Layout and member meanings are inferred from
// soKineticEnergyNormal::init / updateEnergy (HYPOTHESIS names).
class soKineticEnergyNormal : public soKineticEnergy {
public:
    soKineticEnergyNormal() {
        // MATCH-ONLY: the original builds all default vectors first and then copies them member by member.
        Vec2f limit(-1.0f, -1.0f);
        Vec2f brake(0.0f, 0.0f);
        Vec2f target(-1.0f, -1.0f);
        Vec2f accel(0.0f, 0.0f);
        Vec2f speed(0.0f, 0.0f);
        Vec2f::copy(m_speed, speed);
        Vec2f::copy(m_accel, accel);
        Vec2f::copy(m_speedTarget, target);
        Vec2f::copy(m_brake, brake);
        Vec2f::copy(m_speedLimit, limit);
        m_unk30 = false;
        m_considerGroundFriction = false;
        m_unk32 = true;
    }

    virtual void updateEnergy(soModuleAccesser* moduleAccesser);
    virtual Vec2f getSpeed();
    virtual Vec3f getRotation();
    virtual void resetEnergy(int, Vec2f*, Vec3f*, soModuleAccesser* moduleAccesser);
    virtual void clearSpeed();
    virtual void clearRotSpeed();
    virtual void mulSpeed(Vec3f* speed);
    virtual void mulAccel(Vec3f* accel);
    virtual void reflectSpeed(Vec3f* speed);
    virtual void reflectAccel(Vec3f* accel);
    virtual void onConsiderGroundFriction();
    virtual void offConsiderGroundFriction();
    virtual ~soKineticEnergyNormal() { }
    virtual void init();

    Vec2f m_speed;        // +0x08
    Vec2f m_accel;        // +0x10
    Vec2f m_speedTarget;  // +0x18 (init -1,-1)
    Vec2f m_brake;        // +0x20
    Vec2f m_speedLimit;   // +0x28 (init -1,-1)
    bool m_unk30;         // +0x30
    bool m_considerGroundFriction; // +0x31
    bool m_unk32;         // +0x32
};
static_assert(sizeof(soKineticEnergyNormal) == 0x34, "Class is wrong size!");

#ifdef FT_MODULE_BUILDER
// MATCH-ONLY: in the fighter RELs these virtual functions are weak copies (the original header defined them inline);
// sora_melee has the out-of-line versions in so_kinetic_energy_normal.cpp.
inline void soKineticEnergyNormal::clearRotSpeed() { }

inline void soKineticEnergyNormal::clearSpeed() {
    m_speed = Vec2f(0.0f, 0.0f);
}

inline void soKineticEnergyNormal::init() {
    Vec2f zero(0.0f, 0.0f);
    m_speed = m_accel = m_brake = zero;
    Vec2f negOne(-1.0f, -1.0f);
    m_speedTarget = m_speedLimit = negOne;
    m_considerGroundFriction = false;
    m_unk30 = false;
    m_unk32 = true;
}

inline void soKineticEnergyNormal::offConsiderGroundFriction() {
    m_considerGroundFriction = false;
}

inline void soKineticEnergyNormal::onConsiderGroundFriction() {
    m_considerGroundFriction = true;
}

#pragma dont_inline on
inline Vec3f soKineticEnergyNormal::getRotation() {
    return Vec3f(0.0f, 0.0f, 0.0f);
}
#pragma dont_inline off

inline Vec2f soKineticEnergyNormal::getSpeed() {
    return m_speed;
}
#endif
