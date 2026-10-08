#pragma once
// SHADOW of BrawlHeaders/ft/ft_entry.h: addObserver is inline in the fighter RELs (FT_MODULE_BUILDER)
// Also names the flag bytes at 0xF/0x11 and declares the ftEntry member functions the fighter manager (ft_manager.cpp) calls.

#include <StaticAssert.h>
#include <so/event/so_event_presenter.h>
#include <types.h>
#include <ft/ft_input.h>
#include <gm/gm_lib.h>
#include <mt/mt_vector.h>

class Fighter;
class soDamageAttackerInfo;
class ftOwner;

enum ftKind {
    Fighter_Mario = 0x0,
    Fighter_DonkeyKong = 0x1,
    Fighter_Donkey = 0x1,
    Fighter_Link = 0x2,
    Fighter_Samus = 0x3,
    Fighter_Yoshi = 0x4,
    Fighter_Kirby = 0x5,
    Fighter_Fox = 0x6,
    Fighter_Pikachu = 0x7,
    Fighter_Luigi = 0x8,
    Fighter_CaptainFalcon = 0x9,
    Fighter_Captain = 0x9,
    Fighter_Ness = 0xA,
    Fighter_Bowser = 0xb,
    Fighter_Koopa = 0xb,
    Fighter_Peach = 0xc,
    Fighter_Zelda = 0xd,
    Fighter_Sheik = 0xe,
    Fighter_Popo = 0xf,
    Fighter_Nana = 0x10,
    Fighter_Marth = 0x11,
    Fighter_MrGameAndWatch = 0x12,
    Fighter_GameWatch = 0x12,
    Fighter_Falco = 0x13,
    Fighter_Ganondorf = 0x14,
    Fighter_Ganon = 0x14,
    Fighter_Wario = 0x15,
    Fighter_MetaKnight = 0x16,
    Fighter_Pit = 0x17,
    Fighter_ZeroSuitSamus = 0x18,
    Fighter_SZeroSuit = 0x18,
    Fighter_Olimar = 0x19,
    Fighter_Pikmin = 0x19,
    Fighter_Lucas = 0x1a,
    Fighter_DiddyKong = 0x1b,
    Fighter_Diddy = 0x1b,
    Fighter_PokemonTrainer = 0x1c,
    Fighter_PokeTrainer = 0x1c,
    Fighter_Charizard = 0x1d,
    Fighter_PokeLizardon = 0x1d,
    Fighter_Squirtle = 0x1e,
    Fighter_PokeZenigame = 0x1e,
    Fighter_Ivysaur = 0x1f,
    Fighter_PokeFushigisou = 0x1f,
    Fighter_KingDedede = 0x20,
    Fighter_Dedede = 0x20,
    Fighter_Lucario = 0x21,
    Fighter_Ike = 0x22,
    Fighter_ROB = 0x23,
    Fighter_Robot = 0x23,
    Fighter_Jigglypuff = 0x25,
    Fighter_Purin = 0x25,
    Fighter_ToonLink = 0x29,
    Fighter_Wolf = 0x2c,
    Fighter_Snake = 0x2e,
    Fighter_Sonic = 0x2f,
    Fighter_Mewtwo = 0x26,
    Fighter_Roy = 0x27,
    Fighter_PlusleMinun = 0x24,
    Fighter_PraMai = 0x24,
    Fighter_DrMario = 0x28,
    Fighter_ToonZelda = 0x2a,
    Fighter_ToonSheik = 0x2b,
    Fighter_DixieKong = 0x2d,
    Fighter_Dixie = 0x2d,
    Fighter_GigaBowser = 0x30,
    Fighter_GKoopa = 0x30,
    Fighter_WarioMan = 0x31,
    Fighter_Alloy_Red = 0x32,
    Fighter_Zako_Boy = 0x32,
    Fighter_Alloy_Blue = 0x33,
    Fighter_Zako_Girl = 0x33,
    Fighter_Alloy_Yellow = 0x34,
    Fighter_Zako_Child = 0x34,
    Fighter_Alloy_Green = 0x35,
    Fighter_Zako_Ball = 0x35,
    Fighter_MarioD = 0x36,
    Fighter_Count = 0x37,
};
typedef ftKind FighterKind;

class ftEntryEventObserver : public soEventObserver<ftEntryEventObserver> {
public:
#ifdef FT_MODULE_BUILDER
    virtual void addObserver(short param1, s8 param2) { addObserverSub(param1, this, param2); } // MATCH-ONLY: inline in the REL
#else
    virtual void addObserver(short param1, s8 param2);
#endif
    virtual void notifyEventSetDamage(float);
    virtual void notifyEventBeat();
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventDeadPartner(int index) { }
#else
    virtual void notifyEventDeadPartner(int index);
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventPartnerResourcePrepared() { }
#else
    virtual void notifyEventPartnerResourcePrepared();
#endif
    virtual void notifyEventChangeAdvUnit();
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventWarp() { }
#else
    virtual void notifyEventWarp();
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventPokemonStart(int) { }
#else
    virtual void notifyEventPokemonStart(int);
#endif
#ifdef FT_MODULE_BUILDER
    virtual bool notifyEventPokemonRequestChange(Vec3f*, float*) { return false; } // HYPOTHESIS: bool (the REL stub is li r3,0)
#else
    virtual void notifyEventPokemonRequestChange(Vec3f*, float*);
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventPokemonTrainerUpdate() { }
#else
    virtual void notifyEventPokemonTrainerUpdate();
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventPokemonCollect() { }
#else
    virtual void notifyEventPokemonCollect();
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventPokemonChangeCancel() { }
#else
    virtual void notifyEventPokemonChangeCancel();
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventPokemonSpecial(int, int) { }
#else
    virtual void notifyEventPokemonSpecial(int, int);
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventPokemonAppeal() { }
#else
    virtual void notifyEventPokemonAppeal();
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventSetRumble(int, int) { }
#else
    virtual void notifyEventSetRumble(int, int);
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventStopRumble(int) { }
#else
    virtual void notifyEventStopRumble(int);
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventPokemonRebirthEnd() { }
#else
    virtual void notifyEventPokemonRebirthEnd();
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventPokemonAttack() { }
#else
    virtual void notifyEventPokemonAttack();
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventPokemonInflict() { }
#else
    virtual void notifyEventPokemonInflict();
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventPokemonDamage() { }
#else
    virtual void notifyEventPokemonDamage();
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventPokeTrainerReplace(u8) { }
#else
    virtual void notifyEventPokeTrainerReplace(u8);
#endif
    virtual void notifyEventPikminFinalAttack(float, int);
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventKirbyResourceLoaded(int index) { }
#else
    virtual void notifyEventKirbyResourceLoaded(int index);
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventKirbyResourceUnLoaded(int index) { }
#else
    virtual void notifyEventKirbyResourceUnLoaded(int index);
#endif
#ifdef FT_MODULE_BUILDER
    virtual void notifyEventExitFighter(int, int) { }
#else
    virtual void notifyEventExitFighter(int, int);
#endif
    char _spacer1[2];
};
static_assert(sizeof(ftEntryEventObserver) == 12, "Class is wrong size!");

class ftEntry {
public:
    virtual ~ftEntry();

    struct Instance {
        ftKind m_kind;
        Fighter* m_fighter;
    };

    int m_entryId;
    u8 m_entryCount;
    char _0x9;
    s8 m_activeInstanceIndex;
    char _0xb;
    u8 unkC;
    bool m_isReady;
    char _0xe;
    u8 unkF; // 6 means CPU-controlled (ftManager::isCpuActive)
    char _0x10;
    union {
        u8 m_flags11; // flag byte at 0x11, written whole by some callers
        struct {
            bool unk11_80 : 1;
            bool unk11_40 : 1;
            bool unk11_20 : 1;
            bool unk11_10 : 1;
            bool unk11_08 : 1;
            bool unk11_04 : 1;
            u8 unk11_02 : 1; // HYPOTHESIS: set on the partner entry while hearts are swapped (read through isHeartSwapped)
            bool unk11_01 : 1;
        };
    };
    char _0x12[6];
    int m_slotIndex;
    char _0x1c[10];
    u8 m_finalSmashAmount; // custom - how full the FS meter is in REX's FS meter special mode
    char _0x1e[1];
    ftOwner* m_owner;
    ftInput* m_input;
    Instance m_instances[4];
    int m_heartSwapEntryId;
    char _0x54[4];
    int m_playerNo;
    gmCharacterKind m_characterKind;
    int m_pointTeam;
    char _0x64[480];

    bool isHeartSwapped() const { return unk11_02; } // HYPOTHESIS: see unk11_02
    void createInstance();
    void startSubFighter();
    void toStartSequence(u8 mode);
    void setWarp(Vec3f* pos, float lr, u32 flags);
    void standby(int unk);
    void standbyAdvFollow();
    void disappearTrainer();
    int getTeam(bool unk2, bool unk3);
    int getTeam2nd(bool unk);
    void setVisibilityTrainer(bool visible);
    bool isProcessTechnique();
    int isExistFighter(int kind);
    int getCurrentInstanceGmKind();
    void notifyKirbyResourceLoaded(int index);
    void notifyKirbyResourceUnLoaded(int index);
    void notifyExitFighter(int slotIndex, int unk);
    void setTemporaryCamera(float unk1, int unk2, int unk3, int unk4);
    void setIntarpolateTemporaryCamera(float unk1, float unk2, int unk3, int unk4);
    void startChange(int unk1, int unk2, int unk3);
    void prepareChange(float unk1, int unk2, int unk3);
    void setContNo(int contNo);
    bool addDragoon(u32 variation, bool unk);
    void removeDragoon(int index, bool unk);
    void removeDragoonAll(bool unk);
    int getDragoonCount(bool unk);
    int getDragoonVariation(int index, bool unk);
    void setSlow(bool setStatus, int strength, int duration, bool isTimer);
    void toKnockOut(soDamageAttackerInfo* attackerInfo);
    void notifyBeat();
    void setCurry();
    void setZoom(float unk1, int unk2, int unk3);
    void setScaling(int kind, int type); // Fighter::Scaling::Kind, Fighter::Scaling::Type
    void setSuperStar();
    void setHeal(float heal);
    void entryEnd();
    void resultEnd();
    void notifyReplacePokeTrainer(int unk);
    bool setFinal(bool isDiscretion);
    void exitFinal(int unk);
    void leaveBattle(bool unk);
    void notifyDead(int unk);
    void notifyPikminFinalAttack(float unk1, int unk2);
    int getRank();
    int getRankPoint();
};
static_assert(sizeof(ftEntry) == 0x244, "Class is wrong size!");
