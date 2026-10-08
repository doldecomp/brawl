#pragma once

#include <wn/wn_weapon_builder.h>

struct wnYoshiStarModuleAccesserBuildConfig;
struct wnYoshiStarParam {
    float unk0, unk4, unk8, unkC, unk10;
};
static_assert(sizeof(wnYoshiStarParam) == 0x14, "Star float parameter record");

// Original RTTI identifies the natural builder base. Its embedded modules and
// kinetic energies remain opaque while the constructor is unresolved.
template <>
class wnWeaponBuilder<wnYoshiStarModuleAccesserBuildConfig> : public Weapon {
    u8 unkD0[0x1F9C - sizeof(Weapon)];
public:
    virtual ~wnWeaponBuilder();
    virtual void deactivateDescendantForce();
};
static_assert(sizeof(wnWeaponBuilder<wnYoshiStarModuleAccesserBuildConfig>) == 0x1F9C, "Star builder extent");

class wnYoshiStar : public wnWeaponBuilder<wnYoshiStarModuleAccesserBuildConfig> {
    wnYoshiStarParam* m_param;
    u8 unk1FA0[0x30]; // Embedded parameter accesser; original stores establish extent.
public:
    virtual ~wnYoshiStar();
    virtual bool notifyEventCollisionAttackCheck(u32 flags);
    virtual bool notifyEventAnimCmd(acAnimCmd*, soModuleAccesser*, int);
    // HYPOTHESIS: relative source ordering of lr. Native registers establish
    // founder r4, team r5, position r6, and facing f1 independently.
    void activate(int founderTaskId, int team, Vec3f* pos, float lr);
};
static_assert(sizeof(wnYoshiStar) == 0x1FD0, "Star article layout");
