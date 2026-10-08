#pragma once
#include <so/so_kinetic_energy_normal.h>

// Original RTTI includes soKineticEnergyNormal at offset zero. Construction,
// reset, and update establish the additional word at +0x34.
class wnKineticEnergyNormal : public soKineticEnergyNormal {
    int unk34;
public:
    wnKineticEnergyNormal();
    virtual ~wnKineticEnergyNormal();
    virtual void updateEnergy(soModuleAccesser*);
    virtual void resetEnergy(int, Vec2f*, Vec3f*, soModuleAccesser*);
};
static_assert(sizeof(wnKineticEnergyNormal) == 0x38, "Weapon normal energy layout");
