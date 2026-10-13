#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <ut/ut_list.h>

class gfSceneRootEvent : public utListNode {
public:
    virtual void notify(s32 p1) = 0;
};

class gfSceneRootEventList {
    gfSceneRootEvent* head;
public:
    ~gfSceneRootEventList();
    void notify(s32 p1);
};
static_assert(sizeof(gfSceneRootEventList) == 0x4, "Class is the wrong size!");
