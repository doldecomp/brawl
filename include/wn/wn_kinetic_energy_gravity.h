#pragma once
#include <so/kinetic/so_kinetic_energy.h>
// Layout and vertical-motion roles are established by reset/update/accessors,
// the concrete vtable and RTTI, and the Super Sonic builder constructor.
class wnKineticEnergyGravity : public soKineticEnergy {
public:
    wnKineticEnergyGravity() : m_speedY(0.0f), m_gravity(0.0f), m_speedLimit(-1.0f) {}
    virtual void updateEnergy(soModuleAccesser*);
    virtual Vec2f getSpeed();
    virtual Vec3f getRotation();
    virtual void resetEnergy(int, Vec2f*, Vec3f*, soModuleAccesser*);
    virtual void clearSpeed();
    virtual void clearRotSpeed();
    virtual void mulSpeed(Vec3f*);
    virtual void mulAccel(Vec3f*);
    virtual void reflectSpeed(Vec3f*);
    virtual void reflectAccel(Vec3f*);
    virtual ~wnKineticEnergyGravity();
    float m_speedY; // +8: reset/getSpeed/clear/mul use vertical speed.
    float m_gravity; // +C: update adds acceleration, reflect/mulAccel use it.
    float m_speedLimit; // +10: positive bound applied to descending speed.
};
static_assert(sizeof(wnKineticEnergyGravity) == 0x14, "Weapon gravity layout");
