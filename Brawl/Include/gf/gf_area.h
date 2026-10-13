#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <types.h>

class gfArea {

public:
    enum ShapeType {
        Shape_Rectangle = 0x0,
        Shape_Circle = 0x1,
        Shape_Triangle = 0x2,
    };

    enum Group {
        Group_None = 0x0,
        Group_Fighter = 0x1,
        Fighter_Group_Body = 0x1,
        Fighter_Group_Tread_Passive = 0x2,
        Fighter_Group_Tread_Passive_No_Trigger = 0x3,
        Fighter_Group_Item_Pickup = 0x4,

        Group_Enemy = 0x9,
        Enemy_Group_Body = 0x9,
        Enemy_Group_Tread_Passive = 0xA,

        Group_Item = 0x11,
        Item_Group_Body = 0x11,
        Item_Group_Pickup_Small = 0x12,
        Item_Group_Pickup_Large = 0x13,

        Group_Stage = 0x15,
        Stage_Group_Gimmick_Normal = 0x15,
        Stage_Group_Gimmick_Ladder = 0x16,
        Stage_Group_Gimmick_Elevator = 0x17,

        Stage_Group_Space_Normal = 0x19,
        Stage_Group_Space_Wind = 0x1A,
        Stage_Group_Space_Movement_Area = 0x1B,
        Stage_Group_Space_Water = 0x1C,

        Group_Weapon = 0x1D,
        Weapon_Group_Body = 0x1D,
        Weapon_Group_Abnormal = 0x1E,
        Weapon_Group_Spring = 0x1F,
    };

    char _0x0[8];
    int m_checkTargetGroup;
    int m_checkTargetLocalGroup;
    int m_id;
    int m_teamId;
    ShapeType m_shapeType;
    char _0x1C[1];
    Group m_group : 8;
    char _0x1E[2];
    Vec2f m_pos;
    char _0x28[4];
    char _aaabBox[0x10];
    int m_ownerId;
    char _0x40[4];

    virtual bool testIntersectShape(void* unk);
    virtual void debugDrawImp();
    virtual void notifyIntersect(int unk);
    virtual void update();
    virtual bool testIncludePos(Vec2f* pos);
};
static_assert(sizeof(gfArea) == 0x48, "Class is wrong size!");

class gfAreaEventReciver {
public:
    virtual void reciveEvent(gfArea*, gfArea*);
};

typedef gfAreaEventReciver gfAreaEventReceiver;