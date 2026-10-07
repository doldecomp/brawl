#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftSlot_LoadOrder.h>

template s32 soArrayVector<ftSlot::LoadOrder, 16>::getTopIndex() const;
template void soArrayVector<ftSlot::LoadOrder, 16>::setTopIndex(s32);
template s32 soArrayVector<ftSlot::LoadOrder, 16>::getLastIndex() const;
template void soArrayVector<ftSlot::LoadOrder, 16>::setLastIndex(s32);
template ftSlot::LoadOrder& soArrayVector<ftSlot::LoadOrder, 16>::getArrayValueConst(s32);
template void soArrayVector<ftSlot::LoadOrder, 16>::onFull();
template void soArrayVector<ftSlot::LoadOrder, 16>::offFull();
template bool soArrayVector<ftSlot::LoadOrder, 16>::isFull() const;
template s32 soArrayVector<ftSlot::LoadOrder, 16>::capacity() const;
template ftSlot::LoadOrder& soArrayVector<ftSlot::LoadOrder, 16>::atFastAbstractSub(s32) const;
template void soArrayVector<ftSlot::LoadOrder, 16>::setSize(s32);
