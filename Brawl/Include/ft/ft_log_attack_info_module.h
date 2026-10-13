#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/article/so_article.h>
#include <so/so_array.h>

class ftLogAttackInfoModule {
    soArrayVector<soLogAttackInfo, 10> m_logAttackInfoArrayVector;
public:
    ftLogAttackInfoModule();
    ~ftLogAttackInfoModule();
    void addAttackInfo(const soLogAttackInfo&);
    soLogAttackInfo& getAttackInfo(u32);
};
static_assert(sizeof(ftLogAttackInfoModule) == 0x84, "Class is wrong size!");