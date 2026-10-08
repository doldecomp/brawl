#pragma once
#include <wn/wn_weapon_builder.h>
#include <types.h>

// Proved parameter prefix: accessor10054 indexes fields through offset98.
// Complete backing allocation extent remains unreconstructed; no sizeof use.
// HYPOTHESIS: field names await parameter setup/accessor reconstruction; offsets are verified.
struct wnWarioBikeParam {
    u8 unk0[0xC];
    float unkC;
    u8 unk10[0x4];
    float unk14;
    float unk18;
    u8 unk1C[0x4];
    float unk20;
    u8 unk24[0xC];
    float unk30;
    float unk34;
    u8 unk38[0x8];
    float unk40;
    float unk44;
    float unk48;
    float unk4C;
    float unk50;
    float unk54;
    u8 unk58[0x4];
    float unk5C;
    float unk60;
    float unk64;
    float unk68;
    float unk6C;
    int unk70;
    u8 unk74[0x8];
    int unk7C;
    int unk80;
    u8 unk84[0x8];
    float unk8C;
    float unk90;
    float unk94;
    float unk98;
};

// RTTI5FB4 and constructor10318 establish the primary Weapon builder base.
struct wnWarioBikeModuleAccesserBuildConfig;
template <>
class wnWeaponBuilder<wnWarioBikeModuleAccesserBuildConfig> : public Weapon {
    u8 unkD0[0x2980 - sizeof(Weapon)];
public:
    virtual ~wnWeaponBuilder();
    virtual void deactivateDescendantForce();
};
// Proved prefix only: complete allocation size remains HYPOTHESIS.
// No allocation or by-value construction relies on this incomplete field map.
// ConstructorF17C stores the same parameter pointer passed to the accessor at2984.
// The parameter accessor10054 indexes this storage through offset98.
class wnWarioBike : public wnWeaponBuilder<wnWarioBikeModuleAccesserBuildConfig> {
public:
    virtual void processUpdate();
    virtual bool notifyEventCollisionAttackCheck(u32 flags);
    virtual void notifyEventCollisionAttack(float power, soCollisionLog*, soModuleAccesser*);
    virtual void notifyEventLink(soLinkEventArgs*, soModuleAccesser*, StageObject*, int);
    wnWarioBikeParam* m_param;
private:
    u8 unk2984[0xBC]; // Native parameter accessor; detailed fields remain opaque.
};
