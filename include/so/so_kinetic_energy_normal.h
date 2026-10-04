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
    virtual ~soKineticEnergyNormal();
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
