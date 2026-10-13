#pragma once

#include <StaticAssert.h>
#include <so/collision/so_collision_hit_part.h>
#include <so/situation/so_situation_module_impl.h>
#include <types.h>

class soCollisionHitGroup {
public:
    int m_index;
    char _4[2];
    short m_partSize;
    float m_posX;
    float m_scale;
    SituationKind m_situationKind;
    float m_lr;
    char _24[4];
    int m_whole;
    int m_global;
    int m_xluFrameGlobal;
    int m_invincibleFrameGlobal;
    union {
        struct {
            u32 _ : 29;
            bool m_isSituationODD : 1;
            bool m_isSituationAir : 1;
            bool m_isSituationGround : 1;
        };
        soCollision::SituationMask m_multiSituation;
    };
    char _48[1];
    bool m_49;
    bool m_50;
    u8 m_51;
    u8 m_globalOffset;
    char _53[3];

    void setInvincibleGlobal();

    soCollisionHitGroup();
    ~soCollisionHitGroup();
};
static_assert(sizeof(soCollisionHitGroup) == 56, "Class is wrong size!");