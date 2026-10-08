#pragma once

#include <mt/mt_vector.h>
#include <ft/ft_kinetic_energy.h>

class soModuleAccesser;

class ftLuigiKineticTransactor {
public:
    static void changeKinetic(int mode, void* pools, soModuleAccesser* moduleAccesser);
    static void changeKineticSub(bool* result, void* pools, Vec2f* speed, soModuleAccesser* moduleAccesser);
    static void changeKineticSub1(bool* result, void* pools, Vec2f* speed, soModuleAccesser* moduleAccesser);
    static void changeKineticSub2(bool* result, void* pools, Vec2f* speed, soModuleAccesser* moduleAccesser);
    static void changeKineticSub3(bool* result, void* pools, Vec2f* speed, soModuleAccesser* moduleAccesser);
    static void changeKineticSub4(bool* result, void* pools, Vec2f* speed, soModuleAccesser* moduleAccesser);
    static void changeKineticSub5(bool* result, void* pools, Vec2f* speed, soModuleAccesser* moduleAccesser);
    static void changeKineticSub6(bool* result, void* pools, Vec2f* speed, soModuleAccesser* moduleAccesser);
    static void changeKineticSub7(bool* result, void* pools, Vec2f* speed, soModuleAccesser* moduleAccesser);

    template <typename E>
    static void updateEnergy(E* energy, soModuleAccesser* moduleAccesser) {
        if (energy->isEnable() != true) {
            return;
        }
        if (energy->isSuspend()) {
            return;
        }
        energy->updateEnergy(moduleAccesser);
    }

    static void updateEnergy(ftKineticEnergyMotion* energy, soModuleAccesser* moduleAccesser);
    static void updateEnergy(ftKineticEnergyController* energy, soModuleAccesser* moduleAccesser);
};
