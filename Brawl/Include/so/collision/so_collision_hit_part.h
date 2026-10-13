#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <so/so_array.h>
#include <so/collision/so_collision.h>
#include <types.h>

struct soCollisionHitData {
    enum Height {
        Height_Low = 0x1,
        Height_Center = 0x2,
        Height_High = 0x3,
    };

    Vec3f m_startOffsetPos;
    Vec3f m_endOffsetPos;
    float m_size;
    unsigned int m_nodeIndex : 9;
    soCollision::Part m_part : 2;
    Height m_height : 2;
    unsigned int m_0x1c_3 : 2;
    soCollision::ShapeType m_shapeType : 1;
    unsigned int m_0x1c_1 : 16;

    struct Simple {
        Vec3f m_startOffsetPos;
        Vec3f m_endOffsetPos;
        float m_size;
        soCollision::ShapeType m_shapeType : 8;
        char _0x1d[3];
        Height m_height;
        unsigned int m_nodeIndex;
    };
    static_assert(sizeof(Simple) == 40, "Class is wrong size!");

};
static_assert(sizeof(soCollisionHitData) == 32, "Class is wrong size!");

class soCollisionHitPart {
    int m_status;
    char _0x4[4];
    soCollisionHitData m_hitData;
    soArrayVector<clTarget, 6> m_clTargetArrayVector;
    char _0x64[4];

public:
    soCollisionHitPart();
    soCollisionHitPart(soCollision::Category selfCategory, u32 opponentCategory);
    ~soCollisionHitPart();
};
static_assert(sizeof(soCollisionHitPart) == 0x68, "Class is wrong size!");
