#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <ut/ut_list.h>

template <typename T, int C>
class utStageObjectPool {
public:
    T* m_stageObjects;
    u32 m_numStageObjects;
    utList m_list1;
    utList m_list2;
    bool m_32;
    char _pad[3];

    virtual ~utStageObjectPool();
    virtual void clean();
    virtual void reset();
    virtual utListNode* getObject(bool);
    virtual void releaseObject(utListNode*);
};
static_assert(sizeof(utStageObjectPool<utListNode, 0>) == 40, "Class is wrong size!");
