#pragma once

#include <mt/mt_vector.h>
#include <so/kinetic/so_kinetic_energy.h>
#include <types.h>

// Kinetic energies used by fighters (instantiated in the soKineticMediatorImpl type list).
// Only the members that the REL code touches directly are modelled; the rest of the
// classes live in sora_melee.

class soKineticEnergyNormal : public soKineticEnergy {
public:
    u8 m_normalData[0x20 - 0x8]; // TODO: model
};

class ftKineticEnergyMotion : public soKineticEnergyNormal {
public:
};

class ftKineticEnergyController : public soKineticEnergyNormal {
public:
};

class ftKineticEnergyStop : public soKineticEnergyNormal {
public:
    void setBrake(Vec2f* v) { m_brakeX = v->m_x; m_brakeY = v->m_y; }
    float m_brakeX;
    float m_brakeY;
};

class ftKineticEnergyDamage : public ftKineticEnergyStop {
public:
};

class ftKineticEnergyGravity : public soKineticEnergy {
public:
    u8 m_pad[8];
    float m_gravity;
    float m_fallSpeedMax;
};

#include <so/so_module_accesser.h>

// Sum speed helper (the real wrapper is probably an inline function of a util class)
// MWCC only inlines these when each has a single call site in the TU, so the
// wrapper is stamped out once per user (FT_DEFINE_GET_SUM_SPEED(name)).
#define FT_DEFINE_GET_SUM_SPEED(name)     inline Vec2f name(soModuleAccesser* a) {         soKineticEnergy::AttributeFlag flag(1);         return a->getKineticModule().getSumSpeed(flag);     }
