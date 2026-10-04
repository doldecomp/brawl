#pragma once

// soKineticModuleBuilder<soKineticModuleBuildConfig<soKineticModuleGenericImpl, ...>> (0x308 bytes):
// ftMarth fn_106_66DC (ctor, 0x3D0 bytes) / fn_106_3248 (dtor). The kinetic module (soKineticModuleGenericImpl) is at +0.
//   soKineticModuleBuilder(soModuleAccesser*)
// STUB: storage only. Energies of Marth: ftKineticEnergyMotion, Gravity, Controller, Stop, Damage, soKineticEnergyWindNormal,
// soKineticEnergyGroundMovement, soKineticEnergyJostle, held in soInstancePool<soInstancePoolInfo<...>> type lists.

#include <ft/builder/ft_dol_types.h>
#include <types.h>

template <typename T>
class soKineticModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soKineticModuleBuilder {
    u8 m_data[0x308];
public:
    soKineticModuleBuilder(soModuleAccesser* acc) { m_data[0] = 0; m_data[1] = 1; m_data[2] = 2; m_data[3] = 3; m_data[4] = 4; m_data[5] = 5; m_data[6] = 6; m_data[7] = 7; } // STUB
    soKineticModule* getModule() { return (soKineticModule*)m_data; }
};
