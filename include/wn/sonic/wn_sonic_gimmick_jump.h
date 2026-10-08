#pragma once

#include <wn/wn_weapon_builder.h>
#include <so/so_gimmick_event_presenter.h>
#include <ft/ft_kinetic_energy.h>

struct wnSonicGimmickJumpModuleAccesserBuildConfig;

// Original RTTI gives this builder only Weapon as a base. The constructor
// places the spring's observer immediately after the embedded modules.
template <>
class wnWeaponBuilder<wnSonicGimmickJumpModuleAccesserBuildConfig> : public Weapon {
    u8 unkD0[0x2088];
public:
    virtual ~wnWeaponBuilder();
    virtual void deactivateDescendantForce();
};
static_assert(sizeof(wnWeaponBuilder<wnSonicGimmickJumpModuleAccesserBuildConfig>) == 0x2158, "Spring builder size");

class wnSonicGimmickJump : public wnWeaponBuilder<wnSonicGimmickJumpModuleAccesserBuildConfig>, public soGimmickEventObserver {
    void* unk2164;
    u8 unk2168[0x54]; // HYPOTHESIS: embedded parameter accesser, detailed fields unresolved.
    soKineticEnergyGroundMovement m_groundMovement;
public:
    virtual ~wnSonicGimmickJump();
    virtual void onDeactivate();
    virtual void notifyEventChangeStatus(int, int, soStatusData*, soModuleAccesser*);
    virtual void updateNodeSRT();
    virtual void notifyEventGimmick(soGimmickEventArgs*, int*);
    // HYPOTHESIS: relative source ordering of lr; original caller establishes
    // f1 facing and r8 boolean independently of source ordering.
    void activate(int founderTaskId, int resourceId, int team, Vec2f* pos, float lr, bool unk);
    void shoot();
};
static_assert(sizeof(wnSonicGimmickJump) == 0x21EC, "Spring article layout");
