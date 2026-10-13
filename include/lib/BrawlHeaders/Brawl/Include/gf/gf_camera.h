#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <types.h>

class gfCamera {
public:
    struct OrthoParam {
        float m_top;
        float m_bottom;
        float m_left;
        float m_right;
    };

    enum ProjectionType {
        Projection_Orthogonal = 0x0,
        Projection_Perspective = 0x1,
    };

    union TransformFlag {
        u16 m_mask;
        struct {
            bool m_flag15 : 1;      // 0x8000
            bool m_flag14 : 1;      // 0x4000
            bool m_flag13 : 1;      // 0x2000
            bool m_flag12 : 1;      // 0x1000
            bool m_flag11 : 1;      // 0x800
            bool m_flag10 : 1;      // 0x400
            bool m_flag9 : 1;       // 0x200
            bool m_flag8 : 1;       // 0x100
            bool m_flag7 : 1;       // 0x80
            bool m_rotate : 1;       // 0x40
            bool m_flag5 : 1;       // 0x20
            bool m_flag4 : 1;       // 0x10
            bool m_flag3 : 1;       // 0x8
            bool m_flag2 : 1;       // 0x4
            bool m_flag1 : 1;       // 0x2
            bool m_flag0 : 1;       // 0x1
        };
    };

    char _spacer[96];
    Vec3f m_targetPos;
    Vec3f m_centerPos;
    char _0x78[24];
    Vec3f m_0x90;
    Vec3f m_0x9C;
    char _0xA8[24];
    Vec3f m_rot;
    float unkCC;
    float unkD0;
    char _0xD4[8];
    float m_near;
    float m_far;
    char _spacer2[4];
    OrthoParam m_orthoParam;
    TransformFlag m_transformFlag;
    TransformFlag unkFA;

    char _spacer3[4];
    ProjectionType m_projectionType;
    char _spacer4[48];

    void calc();
    void setGX();
    void calcProjection3Dto2D(Vec3f*, Vec2f*);
    void renderDebug();
};
static_assert(sizeof(gfCamera) == 308, "Class is wrong size!");

class gfCameraManager {
public:
    gfCamera m_cameras[6];
    char _spacer[8];

    inline gfCamera* getCamera(u32 index) { return &m_cameras[index]; }

    static gfCameraManager* getManager();
};
static_assert(sizeof(gfCameraManager) == 0x740, "Class is wrong size!");
