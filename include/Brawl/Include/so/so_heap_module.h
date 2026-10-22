#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <sr/sr_common.h>
#include <types.h>

class soHeapModule : public soNullable {
public:
    soHeapModule(bool isNull) : soNullable(isNull) { }
    virtual ~soHeapModule() { }
    virtual HeapType getInstanceHeap() const = 0;
    virtual void setInstanceHeap(HeapType heap) { }
    virtual HeapType getNWModelInstanceHeap() const = 0;
    virtual HeapType getNWMotionInstanceHeap() const = 0;
    virtual u32 getSlotNo() const = 0;
};
static_assert(sizeof(soHeapModule) == 8, "Class is wrong size!");

class soHeapModuleNull : public soHeapModule {
public:
    soHeapModuleNull() : soHeapModule(true) { }
    virtual ~soHeapModuleNull() { }
    virtual HeapType getInstanceHeap() const { return Heaps::Invalid; }
    virtual void setInstanceHeap(HeapType heap) { }
    virtual HeapType getNWModelInstanceHeap() const { return Heaps::Invalid; }
    virtual HeapType getNWMotionInstanceHeap() const { return Heaps::Invalid; }
    virtual u32 getSlotNo() const { return 0; }
};
static_assert(sizeof(soHeapModuleNull) == 8, "Class is wrong size!");
