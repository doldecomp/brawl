#pragma once

#include <StaticAssert.h>
#include <gm/gm_lib.h>
#include <it/it_archive.h>
#include <types.h>

enum itGenId {
    Item_Gen_Assist = 0,
    Item_Gen_AssistTrophy = 0,
    Item_Gen_Barrel = 3,
    Item_Gen_Crate = 7,
    Item_Gen_Box = 7,
    Item_Gen_Capsule = 9,
    Item_Gen_RollingCrate = 10,
    Item_Gen_CarrierBox = 10,
    Item_Gen_PartyBall = 34,
    Item_Gen_Kusudama = 34,
    Item_Gen_Pokemon = 42,
    Item_Gen_PokeBall = 42,
    Item_Gen_Sandbag = 49,
    Item_Gen_Peanut = 84,
    Item_Gen_Basic = 10000,

    // Custom
    Item_Gen_Rain = 10001,
    Item_Gen_Barrel_Enemy = -3,
    Item_Gen_Crate_Enemy = -7,
    Item_Gen_Box_Enemy = -7,
    Item_Gen_Capsule_Enemy = -9,
    Item_Gen_RollingCrate_Enemy = -10,
    Item_Gen_CarrierBox_Enemy = -10,
    Item_Gen_PartyBall_Enemy = -34,
    Item_Gen_Kusudama_Enemy = -34,
};

struct itGenSheetKind {
    Stages::srStageKind m_stageKind;
    int m_levelId;
};

struct itGenParam {
    enum Level {
        Level_VeryEasy = 0x0,
        Level_Easy = 0x1,
        Level_Normal = 0x2,
        Level_Hard = 0x3,
        Level_VeryHard = 0x4
    };

    enum LifeType {
        Life_Normal = 0x0,
        Life_Infinity = 0x1,
    };

    enum AppearKind {
        Appear_None = 0x0,
        Appear_Up = 0x1,
        Appear_Down = 0x2,
        Appear_Fall = 0x3
    };

    struct Entry {
        union {
            struct {
                ItemKind m_itemKind;
            };
            struct {
                itKind m_kind;
                u32 m_variation;
            };
        };
        float m_rate;
        u16 m_minSpawn;
        u16 m_maxSpawn;
    };

    itGenId m_id;
    LifeType m_lifeType;
    AppearKind m_appearKind;
    Entry* m_entries;
    u32 m_numEntries;

};
static_assert(sizeof(itGenParam) == 0x14, "Class is wrong size!");


class itGenArchive {
public:
    itArchive::Type m_itArchiveType;
    itGenSheetKind m_sheetKind;
    int m_archiveId;
    u8 m_16;
    u8 m_17;
    u8 m_18;
    char m_19[1];

    virtual ~itGenArchive();
};
