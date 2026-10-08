#pragma once

#include <ft/builder/ft_builder_kinetic.h>
#include <so/so_kinetic_energy_normal.h>
#include <wn/wn_kinetic_energy_gravity.h>

class soModuleAccesser;

// HYPOTHESIS: these local aliases model the mapped pool type list as the existing
// canonical instance-pool hierarchy; ft_sonic confirms normal at +0x10 and gravity at +0x50.
// The energy indices and attribute masks are mapped as normal <0,1>, gravity <1,1>.
typedef soInstancePoolInfo<soKineticEnergyNormal, 1> wnSonicSuperSonicNormalEnergyInfo;
typedef soKineticEnergyHolder<soKineticEnergyNormal, soTypeListNullType,
                              soKineticEnergyInitInfo<0, 1> > wnSonicSuperSonicNormalEnergyHolder;
typedef soLineInvertHierarchy<wnSonicSuperSonicNormalEnergyInfo,
                              wnSonicSuperSonicNormalEnergyHolder,
                              soInstancePoolRoot> wnSonicSuperSonicNormalEnergyPool;

typedef soInstancePoolInfo<wnKineticEnergyGravity, 1> wnSonicSuperSonicGravityEnergyInfo;
typedef soKineticEnergyHolder<wnKineticEnergyGravity, soTypeListNullType,
                              soKineticEnergyInitInfo<1, 1> > wnSonicSuperSonicGravityEnergyHolder;
typedef soLineInvertHierarchy<wnSonicSuperSonicGravityEnergyInfo,
                              wnSonicSuperSonicGravityEnergyHolder,
                              wnSonicSuperSonicNormalEnergyPool> wnSonicSuperSonicKineticPools;

class wnSonicSuperSonicKineticTransactor {
public:
    static void changeKinetic(int kineticType, wnSonicSuperSonicKineticPools* pools,
                              soModuleAccesser* acc);
    static void changeKineticFinalMoveCommon(wnSonicSuperSonicKineticPools* pools,
                                             soModuleAccesser* acc);
    void changeKineticSub(wnSonicSuperSonicKineticPools* pools, soModuleAccesser* acc);

    static void updateEnergy(soKineticEnergyNormal*, soModuleAccesser*);
    static void updateEnergy(wnKineticEnergyGravity*, soModuleAccesser*);
    static void updateEnergyFinalMoveCommon(soKineticEnergyNormal*, soModuleAccesser*);
    static void updateEnergyFinalMoveCommon(wnKineticEnergyGravity*, soModuleAccesser*);
};
