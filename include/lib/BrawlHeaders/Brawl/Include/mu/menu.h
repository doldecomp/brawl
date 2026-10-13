#pragma once

#include <StaticAssert.h>
#include <gf/gf_scene.h>
#include <mu/mu_menu_controller.h>
#include <types.h>

enum MuSelchkind { /* CSS */
    Selch_Mario=0,
    Selch_Donkey=1,
    Selch_Link=2,
    Selch_Samus=3,
    Selch_SZeroSuit=4,
    Selch_Yoshi=5,
    Selch_Kirby=6,
    Selch_Fox=7,
    Selch_Pikachu=8,
    Selch_Luigi=9,
    Selch_Captain=10,
    Selch_Ness=11,
    Selch_Koopa=12,
    Selch_Peach=13,
    Selch_Zelda=14,
    Selch_Sheik=15,
    Selch_Popo=16,
    Selch_Marth=17,
    Selch_GameWatch=18,
    Selch_Falco=19,
    Selch_Ganon=20,
    Selch_Wario=21,
    Selch_MetaKnight=22,
    Selch_Pit=23,
    Selch_Pikmin=24,
    Selch_Lucas=25,
    Selch_Diddy=26,
    Selch_PokeTrainer=27,
    Selch_PokeLizardon=28,
    Selch_PokeZenigame=29,
    Selch_PokeFushigisou=30,
    Selch_Dedede=31,
    Selch_Lucario=32,
    Selch_Ike=33,
    Selch_Robot=34,
    Selch_Purin=35,
    Selch_ToonLink=36,
    Selch_Wolf=37,
    Selch_Snake=38,
    Selch_Sonic=39,
    Selch_SelectNone=40,
    Selch_Random=41,
    Selch_Boss_BossPackun=45,
    Selch_Boss_Rayquaza=46,
    Selch_Boss_PorkyStatue=47,
    Selch_Boss_Porky=48,
    Selch_Boss_Galleom=49,
    Selch_Boss_Ridley=50,
    Selch_Boss_Duon=51,
    Selch_Boss_MetaRidley=52,
    Selch_Boss_Taboo=53,
    Selch_Boss_MasterHand=54,
    Selch_Boss_CrazyHand=55,
    Selch_Zako_Boy=56,
    Selch_Zako_Girl=57,
    Selch_Zako_Child=58,
    Selch_Zako_Ball=59
};

enum MuStockchkind { /* Cosmetic */
    Stockch_Mario=0,
    Stockch_Donkey=1,
    Stockch_Link=2,
    Stockch_Samus=3,
    Stockch_Yoshi=4,
    Stockch_Kirby=5,
    Stockch_Fox=6,
    Stockch_Pikachu=7,
    Stockch_Luigi=8,
    Stockch_Captain=9,
    Stockch_Ness=10,
    Stockch_Koopa=11,
    Stockch_Peach=12,
    Stockch_Zelda=13,
    Stockch_Sheik=14,
    Stockch_Popo=15,
    Stockch_Marth=16,
    Stockch_GameWatch=17,
    Stockch_Falco=18,
    Stockch_Ganon=19,
    Stockch_Wario=20,
    Stockch_MetaKnight=21,
    Stockch_Pit=22,
    Stockch_SZeroSuit=23,
    Stockch_Pikmin=24,
    Stockch_Lucas=25,
    Stockch_Diddy=26,
    Stockch_PokeTrainer=27,
    Stockch_PokeLizardon=28,
    Stockch_PokeZenigame=29,
    Stockch_PokeFushigisou=30,
    Stockch_Dedede=31,
    Stockch_Lucario=32,
    Stockch_Ike=33,
    Stockch_Robot=34,
    Stockch_Purin=35,
    Stockch_ToonLink=37,
    Stockch_ZeldaSheik=38,
    Stockch_Wolf=39,
    Stockch_Snake=40,
    Stockch_Sonic=41,
    Stockch_Random=42,
    Stockch_Sandbag=43,
    Stockch_Target=44,
    Stockch_Boss_BossPackun=45,
    Stockch_Boss_Rayquaza=46,
    Stockch_Boss_PorkyStatue=47,
    Stockch_Boss_Porky=48,
    Stockch_Boss_Galleom=49,
    Stockch_Boss_Ridley=50,
    Stockch_Boss_Duon=51,
    Stockch_Boss_MetaRidley=52,
    Stockch_Boss_Taboo=53,
    Stockch_Boss_MasterHand=54,
    Stockch_Boss_CrazyHand=55,
    Stockch_Zako_Boy=56,
    Stockch_Zako_Girl=57,
    Stockch_Zako_Child=58,
    Stockch_Zako_Ball=59,
    Stockch_Smash=60,
    Stockch_SelectNone=61
};

enum MuCharKind { /* Record Bank */
    Menu_Char_Mario=0,
    Menu_Char_Donkey=1,
    Menu_Char_Link=2,
    Menu_Char_Samus=3,
    Menu_Char_Yoshi=4,
    Menu_Char_Kirby=5,
    Menu_Char_Fox=6,
    Menu_Char_Pikachu=7,
    Menu_Char_Luigi=8,
    Menu_Char_Captain=9,
    Menu_Char_Ness=10,
    Menu_Char_Koopa=11,
    Menu_Char_Peach=12,
    Menu_Char_Zelda=13,
    Menu_Char_Popo=14,
    Menu_Char_Falco=15,
    Menu_Char_Ganon=16,
    Menu_Char_Wario=17,
    Menu_Char_MetaKnight=18,
    Menu_Char_Pit=19,
    Menu_Char_Pikmin=20,
    Menu_Char_Lucas=21,
    Menu_Char_Diddy=22,
    Menu_Char_Dedede=23,
    Menu_Char_Ike=24,
    Menu_Char_Robot=25,
    Menu_Char_Snake=26,
    Menu_Char_PokeTrainer=27,
    Menu_Char_Lucario=28,
    Menu_Char_Marth=29,
    Menu_Char_GameWatch=30,
    Menu_Char_Purin=31,
    Menu_Char_ToonLink=32,
    Menu_Char_Wolf=33,
    Menu_Char_Sonic=34
};

enum MuStageKind {
    Menu_Stage_Battle = 0,
    Menu_Stage_Final = 1,
    Menu_Stage_Dolpic = 2,
    Menu_Stage_Mansion = 3,
    Menu_Stage_MarioPast = 4,
    Menu_Stage_Kart = 5,
    Menu_Stage_Donkey = 6,
    Menu_Stage_Jungle = 7,
    Menu_Stage_Pirates = 8,
    Menu_Stage_Oldin = 9,
    Menu_Stage_Norfair = 10,
    Menu_Stage_Orpheon = 11,
    Menu_Stage_Crayon = 12,
    Menu_Stage_Halberd = 13,
    Menu_Stage_StarFox = 14,
    Menu_Stage_Stadium = 15,
    Menu_Stage_Tengan = 16,
    Menu_Stage_FZero = 17,
    Menu_Stage_Ice = 18,
    Menu_Stage_GW = 19,
    Menu_Stage_Emblem = 20,
    Menu_Stage_Madein = 21,
    Menu_Stage_Earth = 22,
    Menu_Stage_Palutena = 23,
    Menu_Stage_Famicom = 24,
    Menu_Stage_NewPork = 25,
    Menu_Stage_Village = 26,
    Menu_Stage_MetalGear = 27,
    Menu_Stage_GreenHill = 28,
    Menu_Stage_PictChat = 29,
    Menu_Stage_Plankton = 30,
    Menu_Stage_DxShrine = 31,
    Menu_Stage_DxYorster = 32,
    Menu_Stage_DxGarden = 33,
    Menu_Stage_DxOnett = 34,
    Menu_Stage_DxGreens = 35,
    Menu_Stage_DxCruise = 36,
    Menu_Stage_DxCorneria = 37,
    Menu_Stage_DxBigBlue = 38,
    Menu_Stage_DxZebes = 39,
    Menu_Stage_DxPStadium = 40,
    Menu_Stage_Edit = 41
};

class muMenu : public gfScene {
    //    int activeRumbleController;
    //    int globalRumbleSetting;
    muMenuController m_menuControllers[5];
public:
    virtual void start();
    virtual s32 process();
    virtual s32 exit();
    virtual void init();

    static void loadMenuSound();
    static bool isLoadFinishMenuSound();
    static int exchangeSelchkind2SelCharVoice(int id);
    static int exchangeSelCharVoice2SelCharVoiceLengthE(int id);
    static int exchangeSelCharVoice2SelCharVoiceLengthJ(int id);
    static int exchangeGmCharacterKind2MuStockchkind(int id);
    static int exchangeGmCharacterKind2Something(int id);
    static void startRumbleController(int controller, int rumbleStrength, int rumbleSetting);
    static int exchangeMuSelchkind2MuStockchkind(int id);
    static const char* exchangeMuStockchkind2MuCharName(int id);
    static int getStockFrameID(int id);
    static int getFighterColorFileNo(int charKind, int costumeID);
    static int findCharTeamColorNo(int charKind, int teamColor, int teamSet);

    muMenu(const char* name) : gfScene(name) { }
};
