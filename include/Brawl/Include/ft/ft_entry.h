#pragma once

#include <StaticAssert.h>
#include <so/event/so_event_presenter.h>
#include <types.h>
#include <ft/ft_input.h>
#include <gm/gm_lib.h>
#include <mt/mt_vector.h>

class Fighter;
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
    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventSetDamage(float);
    virtual void notifyEventBeat();
    virtual void notifyEventDeadPartner(int index);
    virtual void notifyEventPartnerResourcePrepared();
    virtual void notifyEventChangeAdvUnit();
    virtual void notifyEventWarp();
    virtual void notifyEventPokemonStart(int);
    virtual void notifyEventPokemonRequestChange(Vec3f*, float*);
    virtual void notifyEventPokemonTrainerUpdate();
    virtual void notifyEventPokemonCollect();
    virtual void notifyEventPokemonChangeCancel();
    virtual void notifyEventPokemonSpecial(int, int);
    virtual void notifyEventPokemonAppeal();
    virtual void notifyEventSetRumble(int, int);
    virtual void notifyEventStopRumble(int);
    virtual void notifyEventPokemonRebirthEnd();
    virtual void notifyEventPokemonAttack();
    virtual void notifyEventPokemonInflict();
    virtual void notifyEventPokemonDamage();
    virtual void notifyEventPokeTrainerReplace(u8);
    virtual void notifyEventPikminFinalAttack(float, int);
    virtual void notifyEventKirbyResourceLoaded(int index);
    virtual void notifyEventKirbyResourceUnLoaded(int index);
    virtual void notifyEventExitFighter(int, int);
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
    char _0xb[2];
    bool m_isReady;
    char _0xe[3];
    u8 _0x11;
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
};
static_assert(sizeof(ftEntry) == 0x244, "Class is wrong size!");
