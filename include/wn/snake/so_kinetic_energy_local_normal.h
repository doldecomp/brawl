#pragma once

#include <so/so_kinetic_energy_normal.h>

// HYPOTHESIS: Snake's local-normal kinetic energy extends the normal 2D
// energy with one scalar at +0x34. Fly status reads/writes that scalar.
class soKineticEnergyLocalNormal : public soKineticEnergyNormal {
public:
    float unk34;
};
static_assert(sizeof(soKineticEnergyLocalNormal) == 0x38, "Local normal energy size");
