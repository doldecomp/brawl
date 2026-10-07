#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftSlot_LoadOrderKirby.h>

template s32 soArrayVector<ftSlot::LoadOrderKirby, 16>::getTopIndex() const;
template void soArrayVector<ftSlot::LoadOrderKirby, 16>::setTopIndex(s32);
template s32 soArrayVector<ftSlot::LoadOrderKirby, 16>::getLastIndex() const;
template void soArrayVector<ftSlot::LoadOrderKirby, 16>::setLastIndex(s32);
template ftSlot::LoadOrderKirby& soArrayVector<ftSlot::LoadOrderKirby, 16>::getArrayValueConst(s32);
template void soArrayVector<ftSlot::LoadOrderKirby, 16>::onFull();
template void soArrayVector<ftSlot::LoadOrderKirby, 16>::offFull();
template bool soArrayVector<ftSlot::LoadOrderKirby, 16>::isFull() const;
template s32 soArrayVector<ftSlot::LoadOrderKirby, 16>::capacity() const;
template ftSlot::LoadOrderKirby& soArrayVector<ftSlot::LoadOrderKirby, 16>::atFastAbstractSub(s32) const;
template void soArrayVector<ftSlot::LoadOrderKirby, 16>::setSize(s32);
