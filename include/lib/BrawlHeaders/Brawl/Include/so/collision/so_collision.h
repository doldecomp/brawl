#pragma once

#include <StaticAssert.h>
#include <so/collision/so_collision_group.h>
#include <gf/gf_task.h>
#include <so/so_array.h>
#include <types.h>

struct clTarget {
    int m_0;
    int m_4;

    clTarget();
    ~clTarget();
};
static_assert(sizeof(clTarget) == 0x8, "Class is wrong size!");

class soCollision {
public:
    enum Category {
        Category_Fighter = 0x0,
        Category_Enemy = 0x1,
        Category_Unk1 = 0x2,
        Category_Item = 0x3,
        Category_Unk2 = 0x4,
        Category_Unk3 = 0x5,
        Category_Gimmick = 0x6,
        Category_Wall = 0x7,
        Category_ItemE = 0x8,
        Category_Floor = 0x9,
    };
    typedef u32 CategoryMask;
    static const CategoryMask CATEGORY_MASK_FIGHTER = 1 << Category_Fighter;
    static const CategoryMask CATEGORY_MASK_ENEMY = 1 << Category_Enemy;
    static const CategoryMask CATEGORY_MASK_ITEM = 1 << Category_Item;
    static const CategoryMask CATEGORY_MASK_GIMMICK = 1 << Category_Gimmick;
    static const CategoryMask CATEGORY_MASK_WALL = 1 << Category_Wall;
    static const CategoryMask CATEGORY_MASK_ITEM_E = 1 << Category_ItemE;
    static const CategoryMask CATEGORY_MASK_FLOOR = 1 << Category_Floor;
    static const CategoryMask CATEGORY_MASK_UNK1 = 1 << Category_Unk1;
    static const CategoryMask CATEGORY_MASK_UNK2 = 1 << Category_Unk2;
    static const CategoryMask CATEGORY_MASK_UNK3 = 1 << Category_Unk3;
    static const CategoryMask CATEGORY_MASK_ALL = CATEGORY_MASK_FIGHTER | CATEGORY_MASK_ENEMY | CATEGORY_MASK_ITEM | CATEGORY_MASK_GIMMICK | CATEGORY_MASK_WALL | CATEGORY_MASK_ITEM_E | CATEGORY_MASK_FLOOR | CATEGORY_MASK_UNK1 | CATEGORY_MASK_UNK2 | CATEGORY_MASK_UNK3;;
    static const CategoryMask CATEGORY_MASK_NO_GIMMICK = CATEGORY_MASK_ALL & ~CATEGORY_MASK_GIMMICK;
    static const CategoryMask CATEGORY_MASK_NO_ITEM = CATEGORY_MASK_ALL & ~CATEGORY_MASK_ITEM & ~CATEGORY_MASK_ITEM_E;

    enum Situation {
        Situation_Ground = 0x0,
        Situation_Air = 0x1,
        Situation_ODD = 0x2,
    };
    typedef u32 SituationMask;
    static const SituationMask SITUATION_MASK_GROUND = 1 << Situation_Ground;
    static const SituationMask SITUATION_MASK_G = SITUATION_MASK_GROUND;
    static const SituationMask SITUATION_MASK_AIR = 1 << Situation_Air;
    static const SituationMask SITUATION_MASK_A = SITUATION_MASK_AIR;
    static const SituationMask SITUATION_MASK_GA = SITUATION_MASK_G | SITUATION_MASK_AIR;
    static const SituationMask SITUATION_MASK_ODD = 1 << Situation_ODD;
    static const SituationMask SITUATION_MASK_ALL = SITUATION_MASK_GROUND | SITUATION_MASK_AIR | SITUATION_MASK_ODD;

    enum Part {
        Part_Body = 0x0,
        Part_Arm = 0x1,
        Part_Knee = 0x2,
        Part_Leg = 0x3
    };
    typedef u32 PartMask;
    static const PartMask PART_MASK_BODY = 1 << Part_Body;
    static const PartMask PART_MASK_ARM = 1 << Part_Arm;
    static const PartMask PART_MASK_KNEE = 1 << Part_Knee;
    static const PartMask PART_MASK_LEG = 1 << Part_Leg;
    static const PartMask PART_MASK_ALL = PART_MASK_BODY | PART_MASK_ARM | PART_MASK_KNEE | PART_MASK_LEG;
    static const PartMask PART_MASK_ETC = PART_MASK_ARM;
    static const PartMask PARK_MASK_LEGS = PART_MASK_LEG | PART_MASK_KNEE;
    static const PartMask PARK_MASK_BODY_LEGS = PART_MASK_BODY | PARK_MASK_LEGS | PART_MASK_KNEE;

    enum ShapeType {
        Shape_Sphere = 0x0,
        Shape_Capsule = 0x1,
    };

    int m_kind;
    int m_indirectTeam;
    soArray<soCollisionGroup>* m_collisionGroupArray;
    int m_taskId;
    gfTask::Category m_taskCategory : 8;
    char _17[2];
    bool m_isNoTeam;
    char _20[4];
};
static_assert(sizeof(soCollision) == 24, "Class is wrong size!");
