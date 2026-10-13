#pragma once

#include <StaticAssert.h>
#include <gr/collision/gr_collision.h>
#include <gr/collision/gr_collision_shape_circle.h>
#include <gr/collision/gr_collision_shape_rhombus.h>
#include <types.h>

class grCollStatus {
public:

    enum TracerType {

    };

    enum Setting {
        Setting_None = 0x0,
        Setting_Ground = 0x1,
        Setting_Air = 0x2,
        Setting_Cliff = 0x3,
    };

    enum TouchId {
        Touch_Up = 0x0,
        Touch_Left = 0x1,
        Touch_Right = 0x2,
        Touch_Down = 0x3,
        Touch_Up_Left = 0x4,
        Touch_Up_Right = 0x5,
        Touch_Down_Left = 0x6,
        Touch_Down_Right = 0x7,
    };
    typedef u8 TouchMask;
    static const TouchMask TOUCH_MASK_NONE = 0x0;
    static const TouchMask TOUCH_MASK_UP = 1 << Touch_Up;
    static const TouchMask TOUCH_MASK_LEFT = 1 << Touch_Left;
    static const TouchMask TOUCH_MASK_RIGHT = 1 << Touch_Right;
    static const TouchMask TOUCH_MASK_DOWN = 1 << Touch_Down;
    static const TouchMask TOUCH_MASK_UP_LEFT = 1 << Touch_Up_Left;
    static const TouchMask TOUCH_MASK_UP_RIGHT = 1 << Touch_Up_Right;
    static const TouchMask TOUCH_MASK_DOWN_LEFT = 1 << Touch_Down_Left;
    static const TouchMask TOUCH_MASK_DOWN_RIGHT = 1 << Touch_Down_Right;
    static const TouchMask TOUCH_MASK_ALL = TOUCH_MASK_UP | TOUCH_MASK_LEFT | TOUCH_MASK_RIGHT | TOUCH_MASK_DOWN | TOUCH_MASK_UP_LEFT | TOUCH_MASK_UP_RIGHT | TOUCH_MASK_DOWN_LEFT | TOUCH_MASK_DOWN_RIGHT;

    // 0
    grCollStatus* m_next;
    // 4
    grCollStatus* m_prev;
    // 8
    Setting m_setting : 8;
    u32 m_0x8_0 : 24;

    char _spacer[2];
    // 14
    union {
        struct {
            u16 : 7;
            bool m_noPassableCheck : 1;
            u16 : 8;
        };
        u16 m_exclusiveLineAttr;
    };
    // 16
    int m_taskId;
    // 20
    char _spacer2[65];
    // 85
    char m_cliffTeam;
    // 86
    char _spacer3[6];
    // 92
    grCollShape* m_prevCollShape;
    // 96
    grCollShape* m_currentCollShape;
    // 100
    char _spacer4[10];
    // 110
    char m_targetLineCategory;
    // 111
    char _spacer5[2];
    // 113
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool m_isCalcLineMove : 1;
    // 114
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool m_isCloudThrough : 1;
    // 115
    bool m_isCloudThroughOut : 1;
    bool : 1;
    bool m_isCorrectIgnoreSlope : 1;
    TracerType m_tracerType : 1;
    bool m_isEventToGround : 1;
    bool : 1;
    bool : 1;
    bool : 1;

    char _116[1];

    // 117

    bool m_touchDown : 1;
    bool m_touchUp : 1;
    bool m_touchLeft : 1;
    bool m_touchRight : 1;
    bool m_touchUpRight : 1;
    bool m_touchUpLeft : 1;
    bool m_touchDownRight : 1;
    bool m_touchDownLeft : 1;

    // 118
    char _spacer6[10];
    // 128
    grCollision* m_collision;
    // 132
    Vec2f m_unk;
    // 140
    Vec2f m_touchLineSpeed;
    // 148
    char _spacer7[32];
    // 180
    Vec2f m_180[3];
    // 204
    char _spacer8[8];
    // 212
    grCollisionLineWork m_collLineWorkArray[19];
    // 516
    grCollShape m_collShape;
    // 520
    char _spacer9[116];
    // TOTAL SIZE == 636
    void getPos(Vec2f*);
};
static_assert(sizeof(grCollStatus) == 636, "Class is wrong size!");

class grCollStatusEventReceiver {
public:
    virtual void receive(int, bool);
};