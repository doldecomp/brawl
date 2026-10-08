#pragma once

#include <wn/wn_weapon_builder.h>
#include <mt/mt_vector.h>

struct wnSonicSuperSonicModuleAccesserBuildConfig;

// Original RTTI identifies Weapon as the builder's sole base. The constructor
// installs its modules within this object; their detailed fields remain opaque.
template <>
class wnWeaponBuilder<wnSonicSuperSonicModuleAccesserBuildConfig> : public Weapon {
    u8 unkD0[0x2C04];
public:
    virtual ~wnWeaponBuilder();
    virtual void deactivateDescendantForce();
};
static_assert(sizeof(wnWeaponBuilder<wnSonicSuperSonicModuleAccesserBuildConfig>) == 0x2CD4, "Sonic weapon builder size");

// HYPOTHESIS: original effect-list type spellings; caller and loop establish
// node, position, scale, entry stride and list layout.
struct wnSonicSuperSonicEffectEntry {
    int nodeId;
    Vec3f pos;
    float scale;
};
struct wnSonicSuperSonicEffectList {
    wnSonicSuperSonicEffectEntry* entries;
    u32 size;
};
static_assert(sizeof(wnSonicSuperSonicEffectEntry) == 0x14, "Super Sonic effect entry size");
static_assert(sizeof(wnSonicSuperSonicEffectList) == 8, "Super Sonic effect list size");

class wnSonicSuperSonic : public wnWeaponBuilder<wnSonicSuperSonicModuleAccesserBuildConfig> {
    u32 unk2CD4;
    u8 unk2CD8[0x58];
public:
    virtual ~wnSonicSuperSonic();
    // HYPOTHESIS: relative source ordering of lr; f1 and integer registers
    // follow the original caller independently of this ordering.
    void activate(int founderTaskId, int resourceId, int team, Vec2f* pos,
                  float lr, SituationKind situation, wnSonicSuperSonicEffectList* effects);
    virtual void processUpdate();
    virtual void updatePosture(bool);
    virtual void notifyEventCollisionAttack(float, soCollisionLog*, soModuleAccesser*);
    virtual bool notifyEventCollisionAttackCheck(u32);
    virtual void notifyEventChangeStatus(int, int, soStatusData*, soModuleAccesser*);
    static int convertSonicNode(int nodeId);
};
static_assert(sizeof(wnSonicSuperSonic) == 0x2D30, "Super Sonic article size");
