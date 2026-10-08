#pragma once

#include <so/kinetic/so_kinetic_energy.h>

// The concrete vtable and reset/getRotation/update methods identify this
// rotational energy. Sonic's constructor places the next module at +0x44.
class soKineticEnergyRotNormal : public soKineticEnergy {
public:
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
    virtual ~soKineticEnergyRotNormal();
    // HYPOTHESIS: argument spelling remains unresolved for this unused empty
    // callback; its additional virtual slot is proved by the concrete table.
    virtual void projectionNormalFollow();

    Vec3f m_rotSpeed;     // +0x08: getRotation and clearRotSpeed
    Vec3f m_accel;        // +0x14: mulAccel and reflectAccel
    Vec3f m_speedTarget;  // +0x20: updateEnergy
    Vec3f m_brake;        // +0x2C: updateEnergy
    Vec3f m_speedLimit;   // +0x38: updateEnergy
};
static_assert(sizeof(soKineticEnergyRotNormal) == 0x44, "Rotational energy size");
