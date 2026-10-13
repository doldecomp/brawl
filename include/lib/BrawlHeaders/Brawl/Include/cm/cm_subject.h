#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <mt/mt_vector.h>

class cmSubject {
public:
    char _0[16];
    Vec3f m_pos;
    char _28[16];
    Rect2D m_range;
    Rect2D m_60;
    Rect2D m_76;
    char _92[40];
};
static_assert(sizeof(cmSubject) == 132, "Class is wrong size!");

class cmSubjectList {
    // TODO
public:
    static cmSubject* getSubjectByPlayerNo(u32 playerNo);
};
