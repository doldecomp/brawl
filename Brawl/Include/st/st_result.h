#pragma once

#include <gm/gm_lib.h>
#include <gr/gr_tengan_event.h>
#include <memory.h>
#include <nw4r/ut/ut_Color.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <gr/gr_gimmick.h>
#include <types.h>

template<typename T>
class stClassInfoImpl<Stages::Result, T> : public stClassInfo {
public:
    stClassInfoImpl() : stClassInfo() {
        setClassInfo(Stages::Result, this);
    };

    virtual ~stClassInfoImpl() {
        setClassInfo(Stages::Result, 0);
    }

    virtual T* create() {
        return T::create();
    }

    virtual void preload() { }
};

struct unkStruct {
    gmCharacterKind _00;
    float m_scale;
    float m_camY[3];
};

unkStruct fighterResultData[] = {
    {Character_SelectNone,          1.0f,  0.0f, 0.0f, 0.0f},
    {Character_Mario,               1.0f,  4.2f, 2.8f, 4.8f},
    {Character_Donkey,              1.0f,  8.5f, 9.0f, 7.0f},
    {Character_Link,                1.0f,  6.0f, 7.5f, 7.0f},
    {Character_Samus,               1.015f,8.0f, 3.5f, 8.0f},
    {Character_SZeroSuit,           1.0f,  6.5f, 3.8f, 7.5f},
    {Character_Yoshi,               1.0f,  6.0f, 5.0f, 5.5f},
    {Character_Kirby,               0.98f, 0.8f, 0.8f, 0.8f},
    {Character_Fox,                 1.08f, 5.5f, 3.5f, 5.5f},
    {Character_Pikachu,             0.96f, 2.5f, 2.0f, 0.0f},
    {Character_Luigi,               1.0f,  0.0f, 6.0f, 5.0f},
    {Character_Captain,             1.05f, 4.0f, 1.8f, 8.0f},
    {Character_Ness,                1.0f,  5.0f, 5.0f, 4.0f},
    {Character_Koopa,               1.0f,  8.0f, 4.5f,10.0f},
    {Character_Peach,               1.0f,  5.5f, 4.0f, 4.5f},
    {Character_Zelda,               1.0f,  4.5f, 5.0f, 4.0f},
    {Character_Sheik,               1.0f,  6.5f, 6.5f, 3.2f},
    {Character_IceClimber,          1.0f,  5.5f, 3.5f, 3.0f},
    {Character_IceClimber_Popo,     1.0f,  5.5f, 3.5f, 3.0f},
    {Character_IceClimber_Nana,     1.0f,  5.5f, 3.5f, 3.0f},
    {Character_Marth,               1.0f,  7.0f, 6.0f, 6.0f},
    {Character_GameWatch,           1.0f,  4.0f, 3.5f, 6.0f},
    {Character_Falco,               1.05f, 3.0f, 3.0f, 5.5f},
    {Character_Ganon,               1.0f,  6.0f, 9.5f, 8.5f},
    {Character_Wario,               1.0f,  5.0f, 7.5f, 3.5f},
    {Character_MetaKnight,          0.95f, 1.5f, 0.5f, 1.0f},
    {Character_Pit,                 1.0f,  1.5f, 7.0f, 4.0f},
    {Character_Pikmin,              0.95f, 2.5f, 1.5f, 3.8f},
    {Character_Lucas,               1.0f,  1.5f, 2.0f, 3.0f},
    {Character_Diddy,               1.0f,  4.0f, 5.8f, 3.0f},
    {Character_Charizard_Trainer,   1.0f,  7.0f, 7.5f, 7.0f},
    {Character_Charizard_Solo,      1.0f,  7.0f, 7.5f, 7.0f},
    {Character_Squirtle_Trainer,    1.03f, 4.5f, 6.5f, 2.0f},
    {Character_Squirtle_Solo,       1.03f, 4.5f, 6.5f, 2.0f},
    {Character_Ivysaur_Trainer,     1.14f, 5.5f, 7.2f, 2.5f},
    {Character_Ivysaur_Solo,        1.14f, 5.5f, 7.2f, 2.5f},
    {Character_Dedede,              0.95f, 7.0f, 7.0f, 6.0f},
    {Character_Lucario,             1.05f, 6.0f, 6.0f, 3.0f},
    {Character_Ike,                 1.0f,  7.5f, 7.0f, 2.5f},
    {Character_Robot,               1.0f,  6.3f, 6.0f, 6.0f},
    {Character_Purin,               1.0f,  1.0f, 1.0f, 1.0f},
    {Character_ToonLink,            1.0f,  3.5f, 4.5f, 4.0f},
    {Character_Wolf,                1.25f, 5.0f, 4.5f, 7.0f},
    {Character_Snake,               1.08f, 9.3f, 2.2f, 2.0f},
    {Character_Sonic,               0.97f, 4.5f, 4.5f, 3.5f},
    {Character_GKoopa,              1.0f,  0.0f, 0.0f, 0.0f},
    {Character_WarioMan,            1.0f,  0.0f, 0.0f, 0.0f},
    {Character_Zako_Boy,            1.0f,  0.0f, 0.0f, 0.0f},
    {Character_Zako_Girl,           1.0f,  0.0f, 0.0f, 0.0f},
    {Character_Zako_Child,          1.0f,  0.0f, 0.0f, 0.0f},
    {Character_Zako_Ball,           1.0f,  0.0f, 0.0f, 0.0f}
};

class stResult : public stMelee {
//    void* m_shrineStageData;
    Vec3f m_positions[12];
    u32 m_winningCharKind;
    u32 m_winAnim;
    u8 unk270;
    int unkState274;
    int unk278;
    Vec3f unk27C;
    float unk288;
    float unk28C;
    float m_fighterRot[4];
    float unk2A0;

  public:
    stResult();
    virtual ~stResult();
    virtual void createObj();
    virtual bool loading();
    virtual void update(float deltaFrame);
    virtual void getFighterStartPos(Vec3f* out, int ftIndex);
    virtual bool isReStartSamePoint() { return false; }
    static stResult* create();
    static stClassInfoImpl<Stages::Result, stResult> bss_loc_14;
};