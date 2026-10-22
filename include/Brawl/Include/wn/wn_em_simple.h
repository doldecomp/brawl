#pragma once

#include <StaticAssert.h>
#include <so/event/so_event_presenter.h>
#include <types.h>
#include <ut/ut_list.h>
#include <wn/wn_weapon_builder.h>

class wnemSimple_ModuleAccesserBuildConfig {
    // TODO
};

class utWeaponObjectBase : public utListNode {
    virtual ~utWeaponObjectBase();
    virtual void setDeactivate(int unk);
};
static_assert(sizeof(utWeaponObjectBase) == 12, "Class is wrong size!");

class wnemSimple : public utWeaponObjectBase, public wnWeaponBuilder<wnemSimple_ModuleAccesserBuildConfig>, public soDamageEventObserver, public soCollisionSearchEventObserver {
public:
    u32 unk2184[0xC];
    u8 unk21B4[0x2];
    bool unk21B6;
    u8 unk21B7[0x1];
    bool unk21B8;
    bool unk21B9;
    u8 unk21BA[0x1];
    bool unk21BB;
    u8 unk21BC[0x18];
    float unk21D4;
    float unk21D8;
    u8 unk21DC[0xC];
    s32 unk21E8;
    s32 unk21EC;
    u8 unk21F0[0x8];
    float unk21F8;
    float unk21FC;
    float unk2200;
    float unk2204;
    u8 unk2208[0xC];
    bool unk2214;
    bool unk2215;
    u8 unk2216[0x2];
    bool unk2218;
    u8 unk2219[0x1B];
    s32* unk2234;
    u8 unk2238[0x13C];

    wnemSimple();
    bool setProcFnc_TouchGround(s32 p1);
    bool setProcFnc_LifeZero(s32 p1);
    bool setProcFnc_HitShell(s32 p1);
    bool setProcFnc_HpZero(s32 p1);
    bool changeProcFnc(s32 p1, s32 p2);
    bool executeAnimCmd(u32 p1);
    bool executeAnimCmd(s32 p1, s32 p2, s32 p3);
    void SetLifeLimit(s32 p1);
    u32 getFrameCounter(s32 p1);
    void RequestDeactive();
    void SetDeadMode();
    virtual ~wnemSimple();
    // TODO: virtual functions
};
static_assert(sizeof(wnemSimple) == 0x2374, "Class is wrong size!");
