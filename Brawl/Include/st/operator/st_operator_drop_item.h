#pragma once

#include <StaticAssert.h>
#include <st/operator/st_operator.h>
#include <mt/mt_vector.h>
#include <types.h>


class stOperatorDropItem : public stOperator {
public:
    static const u32 FRAMES_REQUIRED_START_BOMB_DROP = 1200;

    enum Frequency {
        Frequency_Low = 0x0,
        Frequency_Medium = 0x1,
        Frequency_High = 0x2,
        Frequency_VeryHigh = 0x3, // Custom
        Frequency_Intense = 0x4,  // Custom
        Frequency_BombRain = 0x5  // Custom
    };

    bool m_isSuddenDeath;
    char _0x9[0x3];
    float m_framesElapsedStartBombDrop;
    float m_framesElapsedBombDrop;
    Vec3f m_posItemDrop;
    float m_framesElapsedItemDrop;
    float m_framesRequiredItemDrop;
    float m_framesElapsed;
    Frequency m_frequency : 8;
    char _0x2D[3];

    virtual ~stOperatorDropItem();
};
static_assert(sizeof(stOperatorDropItem) == 112, "Class is wrong size!");

class stOperatorDropItemMelee : public stOperatorDropItem {
public:
    virtual ~stOperatorDropItemMelee();
    virtual void processBegin();
    virtual void startOperator();
};
static_assert(sizeof(stOperatorDropItem) == 112, "Class is wrong size!");

