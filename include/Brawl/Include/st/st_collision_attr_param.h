#pragma once

#include <StaticAssert.h>
#include <gr/gr_yakumono.h>
#include <types.h>

struct grGimmickDamageFloor {
    grGimmick::AttackData m_attackData;
    char _88[4];
    u32 m_index;
    int m_teamNo;

    inline grGimmickDamageFloor() {};
    inline grGimmickDamageFloor(grGimmick::AttackData* attackData, u32 index, int teamNo = -1)
    : m_attackData(*attackData), m_index(index), m_teamNo(teamNo) {
    }

};
static_assert(sizeof(grGimmickDamageFloor) == 100, "Class is wrong size!");
