#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <wn/weapon.h>

template <typename T>
class wnWeaponBuilder : public Weapon {
public:
    char unkD0[0x2090];
    // TODO: virtual functions
};
static_assert(sizeof(wnWeaponBuilder<void>) == 0x2160, "Class is wrong size!");
