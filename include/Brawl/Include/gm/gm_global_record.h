#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <gm/gm_global_mode_melee.h>

struct gmGlobalRecord {

    struct InfoAppFlagData {
        enum State {
            State_Locked = 0x0,
            State_Unlocked = 0x1,
            State_Received = 0x2,
            State_UnlockedReceived = 0x3,
        };

        State m_unlocked75mStage : 2;
        State m_unlockedLuigiMansionStage : 2;
        State m_unlockedWolfFighter : 2;
        State m_unlockedToonLinkFighter : 2;
        State m_unlockedJigglypuffFighter : 2;
        State m_unlockedSonicFighter : 2;
        State m_unlockedMrGameAndWatchFighter : 2;
        State m_unlockedGanondorfFighter : 2;
        State m_unlockedROBFighter : 2;
        State m_unlockedSnakeFighter : 2;
        State m_unlockedLucarioFighter : 2;
        State m_unlockedCaptainFalconFighter : 2;
        State m_unlockedFalcoFighter : 2;
        State m_unlockedLuigiFighter : 2;
        State m_unlockedMarthFighter : 2;
        State m_unlockedNessFighter : 2;
        State m_encounteredCelebi : 2;
        State m_encounteredMew : 2;
        State m_unlockedRandomStageChoice : 2;
        State m_unlockedAdditionalRules : 2;
        State m_unlockedBossBattlesMode : 2;
        State m_unlockedAllStarMode : 2;
        State m_unlockedBigBlueStage : 2;
        State m_unlockedPokemonStadiumStage : 2;
        State m_unlockedGreenGreensStage : 2;
        State m_unlockedJungleJapesStage : 2;
        State m_unlockedFlatZone2Stage : 2;
        State m_unlockedGreenHillZoneStage : 2;
        State m_unlockedHanenbowStage : 2;
        State m_unlockedMarioBrosStage : 2;
        State m_unlockedSpearPillarStage : 2;
        State m_unlockedPirateShipStage : 2;
        State m_filledAllGWChronicleTitles : 2;
        State m_unlockedSMWMasterpiece : 2;
        State m_unlockedOOTMasterpiece : 2;
        State m_unlockedSMB2Masterpiece : 2;
        State m_unlockedFZeroMasterpiece : 2;
        State m_unlockedDonkeyKongMasterpiece : 2;
        State m_unlockedStageBuilderPartsC : 2;
        State m_unlockedStageBuilderPartsB : 2;
        State m_unlockedStageBuilderPartsA : 2;
        State m_unlockedShadowAssist : 2;
        State m_unlockedGrayFoxAssist : 2;
        State m_unlockedBarbaraAssist : 2;
        State m_unlockedInfantryAssist : 2;
        State m_unlockedIsaacAssist : 2;
        State m_unlockedCustomRoboAssist : 2;
        State m_encounteredJirachi : 2;
        State m_have400DifferentTrophies : 2;
        State m_have300DifferentTrophies : 2;
        State m_have200DifferentTrophies : 2;
        State m_have100DifferentTrophies : 2;
        State m_gotAllSubspaceBossTrophies : 2;
        State m_gotAllSubspaceEnemyTrophies : 2;
        State m_filledAllWiiChronicleTitles : 2;
        State m_filledAllDSChronicleTitles : 2;
        State m_filledAllGCNChronicleTitles : 2;
        State m_filledAllGBAChronicleTitles : 2;
        State m_filledAllN64ChronicleTitles : 2;
        State m_filledAllVBChronicleTitles : 2;
        State m_filledAllSNESChronicleTitles : 2;
        State m_filledAllGBChronicleTitles : 2;
        State m_empty : 2;
        State m_filledAllNESChronicleTitles : 2;
        State m_clearedAllStarAllFighters : 2;
        State m_clearedAllStar : 2;
        State m_clearedSubspace : 2;
        State m_clearedClassicAllFighters : 2;
        State m_clearedClassic : 2;
        State m_have250Songs : 2;
        State m_have200Songs : 2;
        State m_have150Songs : 2;
        State m_have100Songs : 2;
        State m_have600DifferentStickers : 2;
        State m_have500DifferentStickers : 2;
        State m_have400DifferentStickers : 2;
        State m_have300DifferentStickers : 2;
        State m_have200DifferentStickers : 2;
        State m_have100DifferentStickers : 2;
        State m_have500DifferentTrophies : 2;
        State m_cleared41SoloEvents : 2;
        State m_cleared20SoloEvents : 2;
        State m_clearedBossBattlesIntense : 2;
        State m_clearedAllStarIntense : 2;
        State m_clearedAllSubspaceStagesIntense : 2;
        State m_clearedClassicIntenseOneStock : 2;
        State m_clearedClassicIntense : 2;
        State m_clearedTargetSmashLevel5AllFighters : 2;
        State m_clearedTargetSmashLevel4AllFighters : 2;
        State m_clearedTargetSmashLevel3AllFighters : 2;
        State m_clearedTargetSmashLevel2AllFighters : 2;
        State m_clearedTargetSmashLevel1AllFighters : 2;
        State m_cleared15MinuteSmash : 2;
        State m_cleared100ManSmash : 2;
        State m_clearedBossBattlesAllFighters : 2;
        State m_clearedBossBattles : 2;
        State m_played10000Matches : 2;
        State m_played1000Matches : 2;
        State m_played100Matches : 2;
        State m_gotAllOnlineFriendIcons : 2;
        State m_filledAllChronicleTitles : 2;
        State m_gotAllMasterpieces : 2;
        State m_gotAllSongs : 2;
        State m_gotAllStageBuilderParts : 2;
        State m_gotAllStickers : 2;
        State m_gotAllTrophies : 2;
        State m_gotAllAssistTrophies : 2;
        State m_gotAllSubspaceMovies : 2;
        State m_gotAllStages : 2;
        State m_gotAllFighters : 2;
        State m_cleared21CoOpEvents : 2;
        State m_cleared10CoOpEvents : 2;
    };
    static_assert(sizeof(InfoAppFlagData) == 28, "Class is wrong size!");

    struct EventHiScoreData {
        u32 m_easyScores[51];
        u32 m_normalScores[51];
        u32 m_hardScores[51];
    };

    struct MenuData {

        union StageSwitch {
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
                bool : 1;
                bool : 1;
                bool m_dxPStadium : 1;
                bool m_dxZebes : 1;
                bool m_dxBigBlue : 1;
                bool m_dxCorneria : 1;
                bool m_dxCruise : 1;
                bool m_dxGreens : 1;
                bool m_dxOnett : 1;
                bool m_dxGarden : 1;
                bool m_dxYorster : 1;
                bool m_dxShrine : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool m_plankton : 1;
                bool m_pictChat : 1;
                bool m_greenHill : 1;
                bool m_metalGear : 1;
                bool m_village : 1;
                bool m_newPork : 1;
                bool m_famicom : 1;
                bool m_palutena : 1;
                bool m_earth : 1;
                bool m_madein : 1;
                bool m_emblem : 1;
                bool m_gW : 1;
                bool m_ice : 1;
                bool m_fZero : 1;
                bool m_tengan : 1;
                bool m_stadium : 1;
                bool m_starFox : 1;
                bool m_halberd : 1;
                bool m_crayon : 1;
                bool m_orpheon : 1;
                bool m_norfair : 1;
                bool m_oldin : 1;
                bool m_pirates : 1;
                bool m_jungle : 1;
                bool m_donkey : 1;
                bool m_kart : 1;
                bool m_marioPast : 1;
                bool m_mansion : 1;
                bool m_dolpic : 1;
                bool m_final : 1;
                bool m_battle : 1;
            };
            struct {
                u32 m_meleeMask;
                u32 m_normalMask;
            };
        };

        u8 m_itemFrequency;
        char _1[7];
        gmItSwitch::ItemSwitch m_itemSwitch;
        char _16[10];
        u8 m_language;
        char _27[5];
        StageSwitch m_stageSwitch;

        bool m_isWidescreen : 1;
        bool m_41_6 : 1;
        bool m_41_5 : 1;
        bool m_41_4 : 1;
        bool m_41_3 : 1;
        bool m_41_2 : 1;
        bool m_41_1 : 1;
        bool m_41_0 : 1;
        char _41[3];
    };

    struct NameData {
        char _0[0x124];
    };
    static_assert(sizeof(NameData) == 0x124, "Class is wrong size!");

    char _0[28];

    InfoAppFlagData m_infoAppFlagData;

    char _56[756];

    EventHiScoreData m_eventHiScoreData[2];

    char _2036[28];

    MenuData m_menuData; // 2064

    char _spacer[0x34B4];
};
static_assert(sizeof(gmGlobalRecord) == 0x3cf0, "Class is wrong size!");

struct nteGlobalData {
    char _spacer[0x88]; // 0x00
};
static_assert(sizeof(nteGlobalData) == 0x88, "Class is wrong size!");


struct gmAdvData {

    struct Record {
        struct LevelClear {
            u32 m_state;           // 0x00
            s32 m_difficulty;      // 0x04
            u32 m_unk1;            // 0x08
            s32 m_percent;         // 0x0C
            u32 m_unk2;            // 0x10
        };
        static_assert(sizeof(LevelClear) == 0x14, "Class is wrong size!");

        char _0[0x04];                    // 0x00
        LevelClear m_levelClears[34]; // 0x04
        char unk2AC[0x467C];
        u32 unk4928;
        u32 unk492C;
    };
    static_assert(sizeof(Record) == 0x4930, "Class is wrong size!");

    Record m_record;
    char unk4930[0x28];
};
static_assert(sizeof(gmAdvData) == 0x4958, "Class is wrong size!");
