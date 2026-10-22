#pragma once

#include <StaticAssert.h>
#include <types.h>

class soArrayVectorCalcInterface;

namespace soArrayVectorCalculator {
    void shift(soArrayVectorCalcInterface& interface, bool isEmpty, s32 capacity, s32 topIndex);
    void pop(soArrayVectorCalcInterface& interface, bool isEmpty, s32 capacity, s32 lastIndex);
    void clear(soArrayVectorCalcInterface& interface);
    s32 unshift(soArrayVectorCalcInterface& interface, bool isFull, s32 capacity, s32 topIndex, s32 lastIndex);
    s32 push(soArrayVectorCalcInterface& interface, bool isFull, s32 capacity, s32 topIndex, s32 lastIndex);
    s32 insert(soArrayVectorCalcInterface& interface, s32 index, bool isFull, s32 size, s32 capacity, s32 topIndex, s32 lastIndex);
    void erase(soArrayVectorCalcInterface& interface, s32 index, s32 size, s32 capacity, s32 topIndex, s32 lastIndex);
    s32 resize(soArrayVectorCalcInterface& interface, s32 size, bool isEmpty, bool isFull, s32 capacity, s32 topIndex, s32 lastIndex);
    void postInitialize(soArrayVectorCalcInterface& interface, s32 size, s32 capacity);
}
