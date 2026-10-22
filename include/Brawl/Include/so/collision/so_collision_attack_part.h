#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <types.h>
#include <so/collision/so_collision.h>
#include <so/so_array.h>
#include <memory.h>

struct soCollisionAttackAbsoluteData {
    int m_power;
    int m_vector;
    int m_reactionEffect;
    int m_reactionFix;
    int m_reactionAdd;
    float m_slipChance;
    float m_hitStopFrame;
    float m_hitStopDelay;
    u32 _32;
};

struct soCollisionAttackData {
    enum Vec {
        Vec_None = 361,
        Vec_Rad = 362,
        Vec_Speed = 363,
        Vec_Random = 364,
        Vec_Sync = 365,
        Vec_Pull_Reaction = 366,
        Vec_Pull = 367,
        Vec_Target_Pos = 368,
    };

    enum Attribute {
        Attribute_Normal = 0x0,
        Attribute_None = 0x1,
        Attribute_Cutup = 0x2,
        Attribute_Electric = 0x3,
        Attribute_Ice = 0x4,
        Attribute_Fire = 0x5,
        Attribute_Coin = 0x6,
        Attribute_Turn = 0x7,
        Attribute_Slip = 0x8,
        Attribute_Sleep = 0x9,
        Attribute_None2 = 0xA,
        Attribute_Bury = 0xB,
        Attribute_Stun = 0xC,
        Attribute_Magic = 0xD,
        Attribute_Flower = 0xE,
        Attribute_YellowSteam = 0xF,    // TODO: real name for this
        Attribute_None3 = 0x10,
        Attribute_Grass = 0x11,
        Attribute_Water = 0x12,
        Attribute_Purple = 0x13,
        Attribute_Paralyze = 0x14,
        Attribute_Aura = 0x15,
        Attribute_Pitfall = 0x16,
        Attribute_Lay = 0x17,
        Attribute_Flinchless = 0x18, // TODO: real name for this?
        Attribute_None5 = 0x19,
        Attribute_None6 = 0x1A,
        Attribute_None7 = 0x1B,
        Attribute_None8 = 0x1C,
        Attribute_None9 = 0x1D,
        Attribute_None10 = 0x1E,
        Attribute_None11 = 0x1F,
    };

    enum SoundLevel {
        Sound_Level_Small = 0x0,
        Sound_Level_S = 0x0,
        Sound_Level_Medium = 0x1,
        Sound_Level_M = 0x1,
        Sound_Level_Large = 0x2,
        Sound_Level_L = 0x2,
        Sound_Level_Largest = 0x3,
        Sound_Level_LL = 0x3,
    };

    enum SoundAttribute {
        Sound_Attribute_None = 0x0,
        Sound_Attribute_Punch = 0x1,
        Sound_Attribute_Kick = 0x2,
        Sound_Attribute_Cutup = 0x3,
        Sound_Attribute_Coin = 0x4,
        Sound_Attribute_Bat = 0x5,
        Sound_Attribute_Harisen = 0x6, // (Harisen)
        Sound_Attribute_Fan = 0x6,
        Sound_Attribute_Elec = 0x7,
        Sound_Attribute_Electric = 0x7,
        Sound_Attribute_Fire = 0x8,
        Sound_Attribute_Water = 0x9,
        Sound_Attribute_Grass = 0xA,
        Sound_Attribute_Bomb = 0xB,
        Sound_Attribute_PeachWeapon = 0xC,
        Sound_Attribute_Snake = 0xD,    // Exclusive to Snake
        Sound_Attribute_Ike = 0xE,      // Exclusive to Ike
        Sound_Attribute_Dedede = 0xF, // Exclusive to Dedede
        Sound_Attribute_Magic = 0x10,
        Sound_Attribute_Kamehit = 0x11, // Shell
        Sound_Attribute_Shell = 0x11, // Shell
        Sound_Attribute_Peach_Binta = 0x12,   // Exclusive to Peach (slap)
        Sound_Attribute_Peach_Slap = 0x12,
        Sound_Attribute_Peach_FryingPan = 0x13,    // Exclusive to Peach
        Sound_Attribute_Peach_Golf = 0x14,   // Exclusive to Peach
        Sound_Attribute_Peach_Tennis = 0x15, // Exclusive to Peach
        Sound_Attribute_Lucario = 0x16, // Exclusive to Lucario
        Sound_Attribute_Marth = 0x17, // Exclusive to Marth
        Sound_Attribute_Mario_Coin = 0x18,   // Exclusive to Mario
        Sound_Attribute_Mario_Final = 0x19, // Exclusive to Mario
        Sound_Attribute_Luigi_Coin = 0x1A,   // Exclusive to Luigi
        Sound_Attribute_Ness_Bat = 0x1B,     // Exclusive to Ness
        Sound_Attribute_Freeze = 0x1C,
    };

    enum SetOffKind {
        SetOff_Off = 0x0,   // transcendent
        SetOff_Thru = 0x2,  // trample (not properly implemented in vBrawl)
        SetOff_On = 0x3,    // clank
    };

    enum LrCheck {
        Lr_Check_Pos = 0x0, // normal reverse hit
        Lr_Check_Speed = 0x1,   // reverse hit based on horizontal momentum
        Lr_Check_Lr = 0x2, // Away from where target is facing
        Lr_Check_Forward = 0x3,  // forward from attacker direction
        Lr_Check_F = 0x3,
        Lr_Check_Reverse = 0x3,
        Lr_Check_Backward = 0x4,    // backward from attacker direction
        Lr_Check_B = 0x4,
        Lr_Check_Along = 0x4,
        Lr_Check_Part = 0x5, // based on where on hitbox you connect / away from center of collision
        // LR_Check_Left/LR_Check_Right/LR_Check_BackSlash?
    };

    enum Region {
        Region_None = 0x0,
        Region_Head = 0x1,
        Region_Body = 0x2,
        Region_Hip = 0x3,
        Region_Punch = 0x4,
        Region_Elbow = 0x5,
        Region_Kick = 0x6,
        Region_Knee = 0x7,
        Region_Throw = 0x8,
        Region_Object = 0x9,
        Region_Sword = 0xA,
        Region_Hammer = 0xB,
        Region_Bomb = 0xC,
        Region_Spin = 0xD,
        Region_Bite = 0xE,
        Region_Magic = 0xF,
        Region_Psi = 0x10,
        Region_Palutena = 0x11,
        Region_Aura = 0x12,
        Region_Bat = 0x13,
        Region_Parasol = 0x14,
        Region_Pikmin = 0x15,
        Region_Water = 0x16,
        Region_Whip = 0x17,
        Region_Tail = 0x18,
        Region_Energy = 0x19
    };

    int m_power;
    Vec3f m_offsetPos;
    float m_size;
    int m_vector;
    int m_reactionEffect;   // kbg
    int m_reactionFix;      // fkb
    int m_reactionAdd;      // bkb
    float m_slipChance;       // trip chance
    float m_hitStopFrame;  // hitstop multiplier
    float m_hitStopDelay;  // sdi multiplier
    union {
        struct {
            unsigned int : 9;    // up to 0x1ff
            bool m_targetCategoryFloor : 1; // Skyword platforms, Hanenbow platforms, stage blocks
            bool m_targetCategoryItemE : 1; // Soccer Ball, Blast Box etc. (items enemies can hit)
            bool m_targetCategoryWall : 1; // Summit ice, Green Hill break, Metal Gear wall, Mario Bros. Pow
            bool m_targetCategoryGimmick : 1; // Ground
            bool m_targetCategory5 : 1;
            bool m_targetCategory4 : 1;
            bool m_targetCategoryItem : 1; // Barrel, Crate etc.
            bool m_targetCategory2 : 1;
            bool m_targetCategoryEnemy : 1; // SSE enemies
            bool m_targetCategoryFighter : 1; // Fighter
            bool m_targetSituationODD : 1;
            bool m_targetSituationAir : 1;
            bool m_targetSituationGround : 1;
            bool : 1;                          // up to 0x1
            bool m_targetPartLeg : 1;                // Usually legs
            bool m_targetPartKnee : 1;                // Usually Shin
            bool m_targetPartArm : 1;                // Usually forearm, wing
            bool m_targetPartBody : 1;                // Usually head, pelvis, upper arm, tail, item
            Attribute : 5;     // up to 0x1f
            SoundLevel : 2; // up to 0x3
            SoundAttribute : 5;   // up to 0x1f
            SetOffKind : 2; // up to 0x3
            bool : 1;
            bool : 1;
            bool : 1;
            bool : 1;
            unsigned int : 9; // up to 0x1ff added shield damage
            unsigned int : 10;     // ~up to 0x3ff
            unsigned int : 16;    // up to 0xffff detectionRate
            bool : 1;
            bool : 1;   // ignore invincibility
            bool : 1; // ignore intangibility
            LrCheck : 3; // up to 0x7
            bool : 1;  // only affect grabbed opponent
            bool : 1;    // friendly fire
            bool : 1;    // no hitlag
            bool : 1; // disable gfx on hit
            bool : 1; // flinchless
            Region : 5; // up to 0x1f;
            bool : 1;
            bool : 1; // custom
            unsigned int : 30; // ~up to 0x3fffffff
        };

        struct {
            unsigned int m_nodeIndex : 9;                     // up to 0x1ff
            soCollision::CategoryMask m_targetCategory : 10;            // up to 0x3ff;
            soCollision::SituationMask m_targetSituation : 3;            // up to 0x7
            bool m_targetLr : 1;                          // up to 0x1 // unused in vBrawl?
            soCollision::PartMask m_targetPart : 4;                 // up to 0xf
            Attribute m_attribute : 5;     // up to 0x1f
            SoundLevel m_soundLevel : 2; // up to 0x3
            SoundAttribute m_soundAttribute : 5;   // up to 0x1f
            SetOffKind m_setOffKind : 2; // up to 0x3
            bool m_noScale : 1;
            bool m_isShieldable : 1;
            bool m_isReflectable : 1;
            bool m_isAbsorbable : 1;
            unsigned int m_subShield : 9; // up to 0x1ff added shield damage
            unsigned int field_0x34_9 : 10;     // ~up to 0x3ff
            unsigned int m_serialHitFrame : 16;    // up to 0xffff detectionRate
            bool m_isDirect : 1;
            bool m_isInvalidInvincible : 1;   // ignore invincibility
            bool m_isInvalidXlu : 1; // ignore intangibility
            LrCheck m_lrCheck : 3; // up to 0x7
            bool m_isCatch : 1;  // only affect grabbed opponent
            bool m_noTeam : 1;    // friendly fire
            bool m_noHitStop : 1;    // no hitlag
            bool m_noEffect : 1; // disable gfx on hit
            bool m_noTransaction : 1; // flinchless
            Region m_region : 5; // up to 0x1f;
            soCollision::ShapeType m_shapeType : 1;
            bool m_isDeath100 : 1; // custom
            unsigned int field_0x3c_2 : 30; // ~up to 0x3fffffff
        };
    };

    inline soCollisionAttackData() {
        m_slipChance = 1.0;
        m_hitStopFrame = 1.0;
        m_hitStopDelay = 1.0;
        m_region = Region_None;
    }

    inline soCollisionAttackData(int power, Vec3f* offsetPos, float size, int vector,
                                 int reactionEffect, int reactionFix, int reactionAdd,
                                 float slipChance, float hitStopFrame, float hitStopDelay,
                                 u32 nodeIndex, soCollision::CategoryMask targetCategory, soCollision::SituationMask targetSituation,
                                 u32 targetLr, soCollision::PartMask targetPart,
                                 Attribute attribute, SoundLevel soundLevel, SoundAttribute soundAttribute,
                                 SetOffKind setOffKind, bool noScale,
                                 bool isShieldable, bool isReflectable, bool isAbsorbable, u32 subShield,
                                 u16 serialHitFrame, bool isDirect, bool isInvalidInvincible, bool isInvalidXlu,
                                 LrCheck lrCheck, bool isCatch, bool noTeam, bool noHitStop, bool noEffect,
                                 bool noTransaction, Region region, soCollision::ShapeType shapeType) {
        MEMINIT(this);
        m_power = power;
        m_offsetPos = *offsetPos;
        m_size = size;
        m_vector = vector;
        m_reactionEffect = reactionEffect;
        m_reactionFix = reactionFix;
        m_reactionAdd = reactionAdd;
        m_slipChance = slipChance;
        m_hitStopFrame = hitStopFrame;
        m_hitStopDelay = hitStopDelay;
        m_nodeIndex = nodeIndex;
        m_targetCategory = targetCategory;
        m_targetSituation = targetSituation;
        m_targetLr = targetLr;
        m_targetPart = targetPart;
        m_attribute = attribute;
        m_soundLevel = soundLevel;
        m_soundAttribute = soundAttribute;
        m_setOffKind = setOffKind;
        m_noScale = noScale;
        m_isShieldable = isShieldable;
        m_isReflectable = isReflectable;
        m_isAbsorbable = isAbsorbable;
        m_subShield = subShield;
        m_serialHitFrame = serialHitFrame;
        m_isDirect = isDirect;
        m_isInvalidInvincible = isInvalidInvincible;
        m_isInvalidXlu = isInvalidXlu;
        m_lrCheck = lrCheck;
        m_isCatch = isCatch;
        m_noTeam = noTeam;
        m_noHitStop = noHitStop;
        m_noEffect = noEffect;
        m_noTransaction = noTransaction;
        m_region = region;
        m_shapeType = shapeType;
    }
};
static_assert(sizeof(soCollisionAttackData) == 64, "Class is wrong size!");

struct soCollisionAttackAbsolute {
    soCollisionAttackData m_attackData;
    char _0x40[4];
    Vec3f m_nodeGlobalPos;
    char _0x50[15];
    u8 m_index;
    int m_groupIndex;
    bool m_isAttack;
    char _0x65[3];

    soCollisionAttackAbsolute();
    ~soCollisionAttackAbsolute();
};

class soCollisionAttackPart {
    enum Status {
        Status_Inactive = 0x0,
        Status_Set = 0x1,
        Status_Active = 0x2
    };

    Status m_status;
    soCollisionAttackData m_attackData;
    soArrayVector<clTarget, 7> m_clTargetArrayVector;
    int m_groupIndex;
    char _0x8c[4];

public:
    soCollisionAttackPart();
    soCollisionAttackPart(soCollision::Category, bool);
    ~soCollisionAttackPart();
};
static_assert(sizeof(soCollisionAttackPart) == 0x90, "Class is wrong size!");
