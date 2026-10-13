#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/article/so_article.h>
#include <so/so_array.h>

class ftLogPatternModule {
    soArrayVector<soLogAttackInfo, 9> m_logAttackInfoArrayVector;
    u8 _0x78;
    char _0x79[3];
public:
    ftLogPatternModule();
    ~ftLogPatternModule();
    void addAttackPattern(const soLogAttackInfo&);
    void clearPattern();
    float getPowerMul(const soLogAttackInfo&);
};
static_assert(sizeof(ftLogPatternModule) == 0x7C, "Class is wrong size!");