#pragma once

#include <so/so_array.h>
#include <so/collision/so_collision_search_event_presenter.h>
#include <so/damage/so_damage_event_presenter.h>
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

// HYPOTHESIS: The config-specific builder owns the opaque region through +0x24F8.
// Constructor calls place the appended observer bases immediately afterward.
template <>
class wnWeaponBuilder<wnSnakeNikitaMissileModuleAccesserBuildConfig> : public Weapon {
    char m_unkBuilderStorage[0x24F8 - sizeof(Weapon)];
};
static_assert(sizeof(wnWeaponBuilder<wnSnakeNikitaMissileModuleAccesserBuildConfig>) == 0x24F8,
              "Snake Nikita missile builder size is wrong");

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