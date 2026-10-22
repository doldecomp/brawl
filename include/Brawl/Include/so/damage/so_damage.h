#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/collision/so_collision_attack_part.h>
#include <so/collision/so_collision_log.h>

class soDamage {
public:
    enum Level {
        Level_1 = 0x0,
        Level_2 = 0x1,
        Level_3 = 0x2,
        Level_Fly = 0x3,
    };

    float m_damage;
    float m_damageAdd;
    float m_powerMax;
    float m_reaction;
    soCollisionLog m_collisionLog;
    soCollisionAttackData m_attackData;
    float m_lr;
    Vec3f m_pos;
    float m_140;
    float m_144;
    float m_damageAdd_;
    int m_attackerTeamOwnerId;
    char _156[4];
};
static_assert(sizeof(soDamage) == 160, "Class is wrong size!"); // size 160

struct soDamageLog {
    float m_reaction;
    soDamage::Level m_level;
    int m_height;
    Vec2f m_speed;
    float m_angle;
    float m_lr;
    float m_frame;
    u32 m_hitStopFrame;
    soCollisionAttackData::Attribute m_attribute;
    float m_damageAdd;
    int m_attackerTeamNo;
    float m_hitStopDelay;
    Vec2f m_groundTouchNormal;
    int m_attackerTaskId;
    int m_attackerTeamOwnerId;
    gfTask::Category m_attackerTaskCategory : 8;
    bool m_isDamageAir : 1;
    bool m_isSituationGround : 1;
    bool : 1;
    bool m_isCollisionAbsolute : 1;
    bool m_isMeteor : 1;
    bool m_isAttackDirect : 1;
    bool m_isVector365 : 1;
    bool : 1;
    char _0x46[2];
};
static_assert(sizeof(soDamageLog) == 0x48, "Class is wrong size!");