#pragma once
#include <so/so_kinetic_energy_normal.h>
#include <wn/wn_kinetic_energy_gravity.h>
class soModuleAccesser;
// Super Sonic's normal and gravity holder callbacks select these overloads.
class wnSonicSuperSonicKineticTransactor {
public:
    static void updateEnergy(soKineticEnergyNormal*, soModuleAccesser*);
    static void updateEnergy(wnKineticEnergyGravity*, soModuleAccesser*);
    static void updateEnergyFinalMoveCommon(soKineticEnergyNormal*, soModuleAccesser*);
    static void updateEnergyFinalMoveCommon(wnKineticEnergyGravity*, soModuleAccesser*);
    // HYPOTHESIS: the three changeKinetic pool-selector signatures await the
    // canonical instance-pool hierarchy repair. Keep the natural TU together.
};
