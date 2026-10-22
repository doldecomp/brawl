#pragma once

#include <StaticAssert.h>
#include <gm/gm_lib.h>
#include <types.h>

class gmItSwitch {
public:
    enum Frequency {
        Frequency_None = 0x0,
        Frequency_Low = 0x1,
        Frequency_Medium = 0x2,
        Frequency_High = 0x3,
        Frequency_VeryHigh = 0x4, // Custom
        Frequency_Intense = 0x5,  // Custom
        Frequency_BombRain = 0x6  // Custom
    };

    struct ItemSwitch {
        union {
            struct {
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool m_cd : 1;
                bool m_trophy : 1;
                bool m_sticker : 1;
                bool m_screwAttack : 1;
                bool m_franklinBadge : 1;
                bool m_teamHealer : 1;
                bool m_soccerBall : 1;
                bool m_unira : 1;
                bool m_spring : 1;
                bool m_bumper : 1;
                bool m_bananaPeel : 1;
                bool m_greenShell : 1;
                bool m_mrSaturn : 1;
                bool m_hothead : 1;
                bool m_pitfall : 1;
                bool m_smokeBall : 1;
                bool m_freezie : 1;
                bool m_dekuNut : 1;
                bool m_smartBomb : 1;
                bool m_gooeyBomb : 1;
                bool m_motionSensorBomb : 1;
                bool m_bobOmb : 1;
                bool m_crackerLauncher : 1;
                bool m_fireFlower : 1;
                bool m_rayGun : 1;
                bool m_superScope : 1;
                bool m_goldenHammer : 1;
                bool m_hammer : 1;
                bool m_starRod : 1;
                bool m_lipStick : 1;
                bool m_fan : 1;
                bool m_homeRunBat : 1;
                bool m_beamSword : 1;
                bool m_lightning : 1;
                bool m_timer : 1;
                bool m_superspicyCurry : 1;
                bool m_bunnyHood : 1;
                bool m_metalBox : 1;
                bool m_starman : 1;
                bool m_warpStar : 1;
                bool m_poisonMushroom : 1;
                bool m_superMushroom : 1;
                bool m_dragoonParts : 1;
                bool m_heartContainer : 1;
                bool m_maximTomato : 1;
                bool m_food : 1;
                bool m_sandBag : 1;
                bool m_blastBox : 1;
                bool m_containers : 1;
                bool m_pokeBall : 1;
                bool m_assistTrophy : 1;
                bool m_smashBall : 1;
            };
            struct { // Custom
                bool m_extra3 : 1;
                bool m_extra2 : 1;
                bool m_extra1 : 1;
                bool m_containerPartyBall : 1;
                bool m_containerRollingCrate : 1;
                bool m_containerCrate : 1;
                bool m_containerBarrel : 1;
                bool m_containerCapsule : 1;
                bool m_containersExplode : 1;
                bool m_containersHaveEnemies : 1;
                bool m_containersHaveItems : 1;
                bool m_passiveAggression : 1;
                bool m_mayhem : 1;
                bool m_extra : 1;
                bool m_stage : 1;
                bool m_screwAttack : 1;
                bool m_franklinBadge : 1;
                bool m_teamHealer : 1;
                bool m_soccerBall : 1;
                bool m_unira : 1;
                bool m_spring : 1;
                bool m_bumper : 1;
                bool m_bananaPeel : 1;
                bool m_greenShell : 1;
                bool m_mrSaturn : 1;
                bool m_hothead : 1;
                bool m_pitfall : 1;
                bool m_smokeBall : 1;
                bool m_freezie : 1;
                bool m_dekuNut : 1;
                bool m_smartBomb : 1;
                bool m_gooeyBomb : 1;
                bool m_motionSensorBomb : 1;
                bool m_bobOmb : 1;
                bool m_crackerLauncher : 1;
                bool m_fireFlower : 1;
                bool m_rayGun : 1;
                bool m_superScope : 1;
                bool m_goldenHammer : 1;
                bool m_hammer : 1;
                bool m_starRod : 1;
                bool m_lipStick : 1;
                bool m_fan : 1;
                bool m_homeRunBat : 1;
                bool m_beamSword : 1;
                bool m_lightning : 1;
                bool m_timer : 1;
                bool m_superspicyCurry : 1;
                bool m_bunnyHood : 1;
                bool m_metalBox : 1;
                bool m_starman : 1;
                bool m_warpStar : 1;
                bool m_poisonMushroom : 1;
                bool m_superMushroom : 1;
                bool m_dragoonParts : 1;
                bool m_heartContainer : 1;
                bool m_maximTomato : 1;
                bool m_food : 1;
                bool m_sandBag : 1;
                bool m_blastBox : 1;
                bool m_containers : 1;
                bool m_pokeBall : 1;
                bool m_assistTrophy : 1;
                bool m_smashBall : 1;
            } ex;
        };
    } m_item;

    struct PokemonSwitch {
        union {
            struct {
                bool : 1;
                bool : 1;
                bool m_bonsly : 1;
                bool m_suicune : 1;
                bool m_wobuffet : 1;
                bool m_gardevoir : 1;
                bool m_goldeen : 1;
                bool m_togepi : 1;
                bool m_piplup : 1;
                bool m_meowth : 1;
                bool m_mew : 1;
                bool m_metagross : 1;
                bool m_electrode : 1;
                bool m_weavile : 1;
                bool m_manaphy : 1;
                bool m_lugia : 1;
                bool m_latiasLatios : 1;
                bool m_kyogre : 1;
                bool m_bellosom : 1;
                bool m_snorlax : 1;
                bool m_jirachi : 1;
                bool m_hoOh : 1;
                bool m_staryu : 1;
                bool m_gulpin : 1;
                bool m_groudon : 1;
                bool m_deoxys : 1;
                bool m_munchlax : 1;
                bool m_moltres : 1;
                bool m_entei : 1;
                bool m_chikorita : 1;
                bool m_celebi : 1;
                bool m_torchic : 1;
            };
            struct { // Custom
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool m_bonsly : 1;
                bool m_suicune : 1;
                bool m_wobuffet : 1;
                bool m_gardevoir : 1;
                bool m_goldeen : 1;
                bool m_togepi : 1;
                bool m_piplup : 1;
                bool m_meowth : 1;
                bool m_metagross : 1;
                bool m_electrode : 1;
                bool m_weavile : 1;
                bool m_manaphy : 1;
                bool m_lugia : 1;
                bool m_latiasLatios : 1;
                bool m_kyogre : 1;
                bool m_bellosom : 1;
                bool m_snorlax : 1;
                bool m_hoOh : 1;
                bool m_staryu : 1;
                bool m_gulpin : 1;
                bool m_groudon : 1;
                bool m_deoxys : 1;
                bool m_munchlax : 1;
                bool m_moltres : 1;
                bool m_entei : 1;
                bool m_chikorita : 1;
                bool m_torchic : 1;
            } ex;
        };
    } m_pokemon;

    struct AssistSwitch {
        bool : 1;
        bool : 1;
        bool : 1;
        bool : 1;
        bool : 1;
        bool m_drWright : 1;
        bool m_waluigi : 1;
        bool m_tingle : 1;
        bool m_infantryTank : 1;
        bool m_starfy : 1;
        bool m_shadow : 1;
        bool m_saki : 1;
        bool m_isaac : 1;
        bool m_mrResetti : 1;
        bool m_nintendog : 1;
        bool m_metroid : 1;
        bool m_littleMac : 1;
        bool m_lyn : 1;
        bool m_jillDozer : 1;
        bool m_katAna : 1;
        bool m_helirin : 1;
        bool m_hammerBro : 1;
        bool m_knuckleJoe : 1;
        bool m_lakitu : 1;
        bool m_jeff : 1;
        bool m_excitebike : 1;
        bool m_devil : 1;
        bool m_samuraiGoroh : 1;
        bool m_rayMKII : 1;
        bool m_grayFox : 1;
        bool m_barbara : 1;
        bool m_andross : 1;
    } m_assist;
};
static_assert(sizeof(gmItSwitch) == 0x10, "Class is wrong size!");

class gmMeleeInitData {
public:
    GameMode m_gameMode : 6;
    char _0x0_0 : 2;
    GameRule m_gameRule : 3;
    u8 m_numPlayers : 3;
    u8 m_0x1_0 : 2;
    bool m_0x2_7 : 1; // 0x02
    bool m_0x2_6 : 1;
    bool m_0x2_5 : 1;
    bool m_0x2_4 : 1;
    bool m_0x2_3 : 1;
    bool m_0x2_2 : 1;
    bool m_0x2_1 : 1;
    bool m_isTeamAttack : 1;
    bool m_0x3_7 : 1; // 0x03
    bool m_0x3_6 : 1;
    bool m_isStamina : 1;
    bool m_0x3_4 : 1;
    bool m_allowPause : 1;
    bool m_0x3_2 : 1;
    bool m_hideDamageGauge : 1;
    bool m_0x3_0 : 1;
    bool m_scoreDisplay : 1; // 0x04
    bool m_0x4_6 : 1;
    bool m_0x4_5 : 1;
    bool m_0x4_4 : 1;
    bool m_0x4_3 : 1;
    bool m_0x4_2 : 1;
    bool m_0x4_1 : 1;
    bool m_0x4_0 : 1;
    char _0x5[0x2];   // 0x05
    bool m_0x7_7 : 1; // 0x07
    bool m_0x7_6 : 1;
    bool m_0x7_5 : 1;
    bool m_0x7_4 : 1;
    bool m_0x7_3 : 1;
    bool m_0x7_2 : 1;
    bool m_0x7_1 : 1;
    bool m_isAmplifySongAttack : 1;
    bool m_playeMode : 1;                        // 0x08
    u8 m_eventId : 7;                          // 0x08
    u8 m_scoreToWin;                           // custom
    char _0xA[0x1];                            // 0x0A
    bool m_isTeams;                            // 0x0B
    gmCorpsKind m_corpsKind : 8;               // 0x0C
    char _0xd[0x1];                            // 0x09
    gmItSwitch::Frequency m_itemFrequency : 8; // 0x0E
    s8 m_suicideScoreMultiplier;               // 0x0F
    char _0x10[0x02];                          // 0x10
    srStageKind m_stageKind : 16;              // 0x12
    u8 m_subStageKind;                         // 0x14
    char _0x15[0x3];                           // 0x15
    s32 m_timeLimitFrames;                     // 0x18
    char _0x1c[0x5];                           // 0x1C
    bool m_isStaminaKnockback : 1;             // custom
    bool m_isStaminaDeadZoneWrap : 1;          // custom
    bool m_isHazardOff : 1;                    // custom
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    char _0x22[6];

    gmItSwitch m_itSwitch;      // 0x28
    char _0x38[0x08];           // 0x38
    float m_cameraShakeScale;   // 0x40
    char _0x44[0x04];           // 0x44
    float m_gameSpeed;          // 0x48
    char _0x4c[0x2C];           // 0x4C
    short m_globalOffenseRatio; // 0x78
    short m_globalDefenseRatio; // 0x7A
    char _0x7c[0x05];           // 0x7C
    u8 m_0x81;                // 0x81
    char _0x82[0x0E];           // 0x82
};
static_assert(sizeof(gmMeleeInitData) == 0x90, "Class is wrong size!");

class gmPlayerInitData {
public:
    gmCharacterKind m_characterKind : 8; // 0x00 (Otherwise known as SlotID)
    u8 m_state;                          // 0x01
    u8 m_playerId;                       // 0x02
    u8 m_playerNo;                       // 0x03
    s8 m_stockCount;                     // 0x04
    s8 m_colorFileNo;                   // 0x05
    s8 m_colorNo;                      // 0x06
    s8 m_controllerNo;                    // 0x07
    s8 m_startPointIdx;                  // 0x08
    char _0x9[0x02];                       // 0x09
    s8 m_teamNo;                         // 0x0B
    wchar_t m_name[5];                   // 0x0c
    char _0x16[2];                          // 0x16
    u8 m_nameIndex;                       // 0x18
    char _0x17;
#ifdef MATCHING
    bool m_isNoVoice;                    // 0x1A
#else
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool m_isNoVoice : 1;
#endif
    bool : 1;                           // 0x1B
    bool : 1;
    bool : 1;
    bool m_isMetal : 1;
    bool : 1;
    bool m_isSpycloak : 1;
    bool : 1;
    bool : 1;
    bool m_isStamina : 1;                // 0x1C
    bool : 1;
    bool : 1;
    bool m_isRebirthXlu : 1;
    bool m_isRabbitCap : 1;
    bool m_isFlower : 1;
    bool m_isCurry : 1;
    bool m_isReflector : 1;
    char _0x1D[1];
    u8 m_cpuType;                        // 0x1E
    u8 m_cpuRank;                        // 0x1F
    char _0x20[0x02];                       // 0x20
    short m_startDamage;                 // 0x22
    short m_hitPointMax;                 // 0x24
    char _0x26[0x02];                       // 0x26
    short m_glowAttack;                  // 0x28
    short m_glowDefense;                 // 0x2A
    float m_attackRatio;                 // 0x2C
    float m_damageRatio;                 // 0x30
    float m_attackReactionMul;           // 0x34
    float m_damageReactionMul;           // 0x38
    char _0x3C[0x04];                       // 0x3C
    float m_scale;                       // 0x40
    float m_visibilityScale;             // 0x44
    float m_gravity;                     // 0x48
    char _0x4C[0x10];                       // 0x4C
};
static_assert(sizeof(gmPlayerInitData) == 0x5C, "Class is wrong size!");

class gmGlobalModeMelee {
public:
    char _0[0x08];                         // 0x00
    gmMeleeInitData m_meleeInitData;       // 0x08
    gmPlayerInitData m_playersInitData[MAX_PLAYERS]; // 0x98
    char _1[4];
};
static_assert(sizeof(gmGlobalModeMelee) == 0x320, "Class is wrong size!");