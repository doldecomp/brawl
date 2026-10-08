#pragma once

#include <ft/builder/ft_builder_kinetic.h>
#include <so/so_kinetic_energy_normal.h>
#include <wn/wn_kinetic_energy_gravity.h>

class soModuleAccesser;

// The native Wario bike mediator owns normal energies at indices 0 and 2,
// with a vertical gravity energy at index 1. These pool types follow the
// concrete template names in the ft_wario map and the mediator's getInstanceAt
// callsites.
typedef soInstancePoolInfo<soKineticEnergyNormal, 1> wnWarioBikeNormal0Info;
typedef soKineticEnergyHolder<soKineticEnergyNormal, soTypeListNullType,
                              soKineticEnergyInitInfo<0, 1> > wnWarioBikeNormal0Holder;
typedef soLineInvertHierarchy<wnWarioBikeNormal0Info, wnWarioBikeNormal0Holder,
                              soInstancePoolRoot> wnWarioBikeNormal0Pool;

typedef soInstancePoolInfo<wnKineticEnergyGravity, 1> wnWarioBikeGravityInfo;
typedef soKineticEnergyHolder<wnKineticEnergyGravity, soTypeListNullType,
                              soKineticEnergyInitInfo<1, 1> > wnWarioBikeGravityHolder;
typedef soLineInvertHierarchy<wnWarioBikeGravityInfo, wnWarioBikeGravityHolder,
                              wnWarioBikeNormal0Pool> wnWarioBikeGravityPool;

typedef soInstancePoolInfo<soKineticEnergyNormal, 1> wnWarioBikeNormal2Info;
typedef soKineticEnergyHolder<soKineticEnergyNormal, soTypeListNullType,
                              soKineticEnergyInitInfo<2, 1> > wnWarioBikeNormal2Holder;
typedef soLineInvertHierarchy<wnWarioBikeNormal2Info, wnWarioBikeNormal2Holder,
                              wnWarioBikeGravityPool> wnWarioBikeKineticPools;

// HYPOTHESIS: the map-derived transactor owns the custom bike selector policy;
// its exact runtime configuration is supplied by the Wario bike mediator.
class wnWarioBikeKineticTransactor {
    u8 m_dummy;
public:
    static void changeKinetic(int kineticType, wnWarioBikeKineticPools* pools,
                              soModuleAccesser* accesser);
    void changeKineticSub(wnWarioBikeKineticPools* pools, soModuleAccesser* accesser);
    void changeKineticSub1(wnWarioBikeKineticPools* pools, soModuleAccesser* accesser);
    void changeKineticSub2(wnWarioBikeKineticPools* pools, soModuleAccesser* accesser);
    void changeKineticSub3(wnWarioBikeKineticPools* pools, soModuleAccesser* accesser);
    void changeKineticSub4(wnWarioBikeKineticPools* pools, soModuleAccesser* accesser);
    void changeKineticSub5(wnWarioBikeKineticPools* pools, soModuleAccesser* accesser);
    void changeKineticSub6(wnWarioBikeKineticPools* pools, soModuleAccesser* accesser);
    void changeKineticSub7(wnWarioBikeKineticPools* pools, soModuleAccesser* accesser);
    void changeKineticSub8(wnWarioBikeKineticPools* pools, soModuleAccesser* accesser);

    static void updateEnergy(soKineticEnergyNormal* energy, soModuleAccesser* accesser);
    static void updateEnergy1(wnKineticEnergyGravity* energy, soModuleAccesser* accesser);
};
