#pragma once

#include <StaticAssert.h>
#include <gr/collision/gr_collision_data.h>
#include <gr/collision/gr_collision_line.h>
#include <mt/mt_coll2d.h>
#include <mt/mt_matrix.h>
#include <types.h>

class grCollision;
class Ground;

class grCollisionJoint {
public:
    // 0
    char _spacer[16];
    // 16
    clAABBox2D m_aabBox;
    // 32
    char _spacer2[16];
    // 48
    grCollision* m_collision;
    // 52
    grCollisionLine* m_lines;
    // 56
    grCollData::VtxData* m_vtxDatas;
    // 60
    char _spacer3[12];
    // 72
    bool m_0x48_31 : 1;
    bool m_0x48_30 : 1;
    bool m_0x48_29 : 1;
    bool m_0x48_28 : 1;
    bool m_0x48_27 : 1;
    bool m_0x48_26 : 1;
    bool m_0x48_25 : 1;
    bool m_0x48_24 : 1;
    bool m_0x48_23 : 1;
    bool m_0x48_22 : 1;
    bool m_0x48_21 : 1;
    bool m_0x48_20 : 1;
    bool m_0x48_19 : 1;
    bool m_0x48_18 : 1;
    bool m_0x48_17 : 1;
    bool m_0x48_16 : 1;
    bool m_0x48_15 : 1;
    bool m_0x48_14 : 1;
    bool m_0x48_13 : 1;
    bool m_0x48_12 : 1;
    bool m_0x48_11 : 1;
    bool m_0x48_10 : 1;
    bool m_0x48_9 : 1;
    bool m_0x48_8 : 1;
    bool m_0x48_7 : 1;
    bool m_0x48_6 : 1;
    bool m_0x48_5 : 1;
    bool m_0x48_4 : 1;
    bool m_0x48_3 : 1;
    bool m_0x48_2 : 1;
    bool m_0x48_1 : 1;
    bool m_0x48_0 : 1;

    u16 m_vtxLen;

    u16 _0x4E;

    // 80
    u16 m_nodeIndex;
    // 82
    union {
        struct {
            bool m_0x52_15 : 1;
            bool m_rightLedgeDisabled : 1;
            bool m_leftLedgeDisabled : 1;
            bool m_0x52_12 : 1;
            bool m_0x52_11 : 1;
            bool m_0x52_10 : 1;
            bool m_0x52_9 : 1;
            bool m_0x52_8 : 1;
            bool m_0x52_7 : 1;
            bool m_0x52_6 : 1;
            bool m_0x52_5 : 1;
            bool m_0x52_4 : 1;
            bool m_0x52_3 : 1;
            bool m_0x52_2 : 1;
            bool m_0x52_1 : 1;
            bool m_0x52_0 : 1;
        };
        u16 m_0x52;
    };

    // 84
    bool m_0x54_7 : 1;
    bool m_0x54_6 : 1;
    bool m_0x54_5 : 1;
    bool m_0x54_4 : 1;
    bool m_0x54_3 : 1;
    bool m_0x54_2 : 1;
    bool m_0x54_1 : 1;
    bool m_0x54_0 : 1;
    // 85
    bool m_0x55_7 : 1;
    bool m_0x55_6 : 1;
    bool m_0x55_5 : 1;
    bool m_0x55_4 : 1;
    bool m_0x55_3 : 1;
    bool m_0x55_2 : 1;
    bool m_0x55_1 : 1;
    bool m_0x55_0 : 1;
    // 86
    bool m_0x56_7 : 1;
    bool m_0x56_6 : 1;
    bool m_0x56_5 : 1;
    bool m_0x56_4 : 1;
    bool m_0x56_3 : 1;
    bool m_0x56_2 : 1;
    bool m_0x56_1 : 1;
    bool m_0x56_0 : 1;
    // 88
    Ground* m_ground;
    // 92
    Matrix* m_matrix;

    grCollisionLine* getLine(u16 index);
};
static_assert(sizeof(grCollisionJoint) == 96, "Class is wrong size!");