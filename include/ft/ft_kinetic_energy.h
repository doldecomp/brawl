#pragma once

#include <mt/mt_vector.h>
#include <so/kinetic/so_kinetic_energy.h>
#include <ft/ft_kinetic_energy_controller.h>
#include <so/so_kinetic_energy_normal.h>
#include <types.h>

// Kinetic energies used by fighters (instantiated in the soKineticMediatorImpl type list).
// Only the members that the REL code touches directly are modelled; the rest of the
// classes live in sora_melee.

class ftKineticEnergyMotion : public soKineticEnergyNormal {
public:
#ifdef FT_MODULE_BUILDER
    ftKineticEnergyMotion(); // sora_melee
#endif
#ifdef FT_MODULE_BUILDER
    virtual ~ftKineticEnergyMotion() { }
#endif
    int m_motionMode; // +0x34
    u32 unk38;
    float unk3C;
    float unk40;
    u8 unk44[0xc];
};

class ftKineticEnergyStop : public soKineticEnergyNormal {
public:
#ifdef FT_MODULE_BUILDER
    ftKineticEnergyStop(); // sora_melee
#endif
#ifdef FT_MODULE_BUILDER
    virtual ~ftKineticEnergyStop() { }
#endif
    void setBrake(Vec2f* v) { m_brakeX = v->m_x; m_brakeY = v->m_y; }
    float m_brakeX;
    float m_brakeY;
};

class ftKineticEnergyDamage : public ftKineticEnergyStop {
public:
#ifdef FT_MODULE_BUILDER
    ftKineticEnergyDamage() { }
#endif
#ifdef FT_MODULE_BUILDER
    virtual ~ftKineticEnergyDamage() { }
#endif
};

class ftKineticEnergyGravity : public soKineticEnergy {
public:
#ifdef FT_MODULE_BUILDER
    ftKineticEnergyGravity(); // sora_melee
#endif
#ifdef FT_MODULE_BUILDER
    virtual ~ftKineticEnergyGravity() { }
#endif
    u8 m_pad[8];
    float m_gravity;
    float m_fallSpeedMax;
    u8 m_unk18[0x10];
};

// HYPOTHESIS: the real layouts are unknown, only the sizes are (from the soKineticMediatorImpl pool layout).
class soKineticEnergyWindNormal : public soKineticEnergyNormal {
public:
#ifdef FT_MODULE_BUILDER
    soKineticEnergyWindNormal(); // sora_melee
#endif
#ifdef FT_MODULE_BUILDER
    virtual ~soKineticEnergyWindNormal() { }
#endif
    u8 m_unk34[0xc];
};

class soKineticEnergyGroundMovement : public soKineticEnergy {
public:
#ifdef FT_MODULE_BUILDER
    soKineticEnergyGroundMovement(); // sora_melee
#endif
#ifdef FT_MODULE_BUILDER
    virtual ~soKineticEnergyGroundMovement() { }
#endif
    u8 m_unk08[0x28];
};

class soKineticEnergyJostle : public soKineticEnergy {
public:
#ifdef FT_MODULE_BUILDER
    soKineticEnergyJostle(); // sora_melee
#endif
#ifdef FT_MODULE_BUILDER
    virtual ~soKineticEnergyJostle() { }
#endif
    u8 m_unk08[0xc];
};

#include <so/so_module_accesser.h>

// Sum speed helper (the real wrapper is probably an inline function of a util class)
// MWCC only inlines these when each has a single call site in the TU, so the
// wrapper is stamped out once per user (FT_DEFINE_GET_SUM_SPEED(name)).
#define FT_DEFINE_GET_SUM_SPEED(name)     inline Vec2f name(soModuleAccesser* a) {         soKineticEnergy::AttributeFlag flag(1);         return a->getKineticModule().getSumSpeed(flag);     }
