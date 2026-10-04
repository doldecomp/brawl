#pragma once

#include <StaticAssert.h>
#include <ft/ft_entry.h>
#include <so/so_null.h>
#include <sr/sr_common.h>
#include <types.h>

// NOTE: This header shadows the one in BrawlHeaders (include/ comes first in the search path).
// The real signature of create() takes the constructor arguments of the fighter class.
class Fighter;

class ftClassInfo : private soNull, public soNullable {
public:
    ftClassInfo(bool isNull = false);

    virtual ~ftClassInfo();
    virtual Fighter* create(s32 entryId, Heaps::HeapType instHeap, Heaps::HeapType nwModelInstHeap, Heaps::HeapType nwMotionInstHeap) const = 0;

    void setClassInfo(ftKind kind, ftClassInfo* info);
    static ftClassInfo* getClassInfo(ftKind kind);
};
static_assert(sizeof(ftClassInfo) == 0xC, "Class is the wrong size!");

class ftClassInfoNull : public ftClassInfo {
public:
    ftClassInfoNull() : ftClassInfo(true) { }

    virtual ~ftClassInfoNull();
    virtual Fighter* create(s32 entryId, Heaps::HeapType instHeap, Heaps::HeapType nwModelInstHeap, Heaps::HeapType nwMotionInstHeap) const;
};
static_assert(sizeof(ftClassInfoNull) == 0xC, "Class is the wrong size!");

extern ftClassInfoNull g_ftClassInfoNull;
