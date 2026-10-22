#pragma once

#include <StaticAssert.h>
#include <gr/collision/gr_collision_status.h>
#include <mt/mt_vector.h>
#include <types.h>

class soModuleAccesser;

class soGroundShapeImpl {
public:
    enum ShapeKind {
        Shape_Rhombus_Modify = 0x0,
        Shape_Rhombus = 0x1,
        Shape_Rhombus_Follow_Node = 0x2,
    };

    enum ShapeFlagId {
        Shape_Flag_Ground = 0x0,
        Shape_Flag_Ignore_Scale = 0x1,

        Shape_Rhombus_Flag_Min_L = 0x3,
        Shape_Rhombus_Flag_Min_R = 0x4,
        Shape_Rhombus_Flag_Min_U = 0x5,
        Shape_Rhombus_Flag_Min_D = 0x6,

        Shape_Rhombus_Modify_Flag_Fix = 0x3,
        Shape_Rhombus_Modify_Flag_No_OFS = 0x4,
        Shape_Rhombus_Modify_Flag_Min_U = 0x5,
        Shape_Rhombus_Modify_Flag_Min_LR = 0x6,
        Shape_Rhombus_Modify_Flag_No_Modify = 0x7,
        Shape_Rhombus_Modify_Flag_Free_Y = 0x8,
        Shape_Rhombus_Modify_Flag_Front_Fix = 0x9,
        Shape_Rhombus_Modify_Flag_Up_Fix = 0xa,
    };

    enum CorrectKind {
        Correct_None = 0x0,
        Correct_Ground = 0x1,
        Correct_Ground_Cliff_Stop = 0x2,
        Correct_Ground_Ottotto = 0x3,
        Correct_Cliff = 0x4,
        Correct_Air = 0x5,
        Correct_Air_Passable = 0x6,
        Correct_Keep = 0x7,
        Correct_Ground_Cliff_Stop_Front = 0x8,
    };

    enum CliffCheckKind {
        Cliff_Check_None = 0x0,
        Cliff_Check_Always = 0x1,
        Cliff_Check_Always_Both_Sides = 0x2,
        Cliff_Check_On_Drop = 0x3,
        Cliff_Check_On_Drop_Both_Sides = 0x4,
    };

    char _0[4];
    grCollStatus* m_collStatus;
    Vec2f m_savePos;
    Vec2f m_offset;
    float m_24;
    float m_28;
    float m_rhombusUp;
    float m_rhombusDown;
    float m_rhombusWidth;
    int m_rhombusFollowNode;
    float m_downFriction;
    grCollisionLine::MaterialType m_collMaterialType : 8;
    char _53;
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
            bool : 1;
            bool : 1;
            bool m_ignoreScale : 1;
            bool m_ground : 1;
        };
        union {
            struct {
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool m_upFix : 1;
                bool m_frontFix : 1;
                bool m_freeY : 1;
                bool m_noModify : 1;
                bool m_minLR : 1;
                bool m_minU : 1;
                bool m_noOFS : 1;
                bool m_fix : 1;
                bool : 1;
                bool : 1;
                bool : 1;
            } m_rhombus;
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
                bool m_minD : 1;
                bool m_minU : 1;
                bool m_minR : 1;
                bool m_minL : 1;
                bool : 1;
                bool : 1;
                bool : 1;
            } m_rhombusModify;
        };
    } m_flag;

    CorrectKind m_correctKind : 8;
    CliffCheckKind m_cliffCheck : 8;
    ShapeKind m_shapeKind : 4;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool m_testPreMap : 1;
    bool m_testDynamicCollision : 1;
    bool m_testCollStop : 1;

    char _60[4];

    virtual ~soGroundShapeImpl();

    void updateRhombus(soModuleAccesser* moduleAccesser);
    void updateRhombusFollowNode(soModuleAccesser* moduleAccesser);
    void updateRhombusModify(soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soGroundShapeImpl) == 68, "Class is wrong size!");