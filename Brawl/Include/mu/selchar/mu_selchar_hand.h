#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <mu/selchar/mu_selchar_coin.h>
#include <types.h>

class muSelCharPlayerArea;

class muSelCharHand : public gfTask {
public:
    char _0x40[0x5C];
    muSelCharPlayerArea* m_selCharPlayerArea;
    muSelCharCoin* m_selCharCoin;
    int m_mode;
    char _0xa0[0x4];
    int m_collKind;
    char _0xb0[0x18];
    int m_bButtonCnt;
    float _0xcc;
    char _0xd0[0x10];

    virtual void processDefault();
    virtual ~muSelCharHand();
};
static_assert(sizeof(muSelCharHand) == 0xe0, "Class is wrong size!");