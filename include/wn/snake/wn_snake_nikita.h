#pragma once

#include <so/so_array.h>
#include <wn/wn_weapon_builder.h>
#include <wn/weapon.h>

struct wnSnakeNikitaModuleAccesserBuildConfig;
struct wnSnakeNikitaMissileModuleAccesserBuildConfig;

// HYPOTHESIS: The constructor places the missile-task vector immediately
// after the owner builder's embedded module storage at +0x67B0.
template <>
class wnWeaponBuilder<wnSnakeNikitaModuleAccesserBuildConfig> : public Weapon {
    char m_unkBeforeMissileTaskIds[0x67B0 - sizeof(Weapon)];
};

// HYPOTHESIS: The missile builder's embedded module layout is omitted here.
// Its primary Weapon base and RTTI identity are verified; callbacks do not
// allocate this type or access the omitted builder storage.
template <>
class wnWeaponBuilder<wnSnakeNikitaMissileModuleAccesserBuildConfig> : public Weapon {};

class wnSnakeNikita : public wnWeaponBuilder<wnSnakeNikitaModuleAccesserBuildConfig> {
public:
    virtual void notifyEventLink(soLinkEventArgs* eventInfo, soModuleAccesser* moduleAccesser,
                                 StageObject* linkedObject, int unk4);
    virtual void onDeactivate();
    void forceFallMissile();

private:
    void notifyEnd(int isEnd);

    // HYPOTHESIS: The constructor's soArrayVector_Ul_2 at this offset records
    // task IDs for Nikita missiles managed by this owner.
    soArrayVector<unsigned long, 2> m_unkMissileTaskIds;
};