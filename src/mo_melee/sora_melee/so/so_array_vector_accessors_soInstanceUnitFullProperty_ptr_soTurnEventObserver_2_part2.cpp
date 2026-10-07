#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soTurnEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 2>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 2>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 2>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 2>::setLastIndex(s32);
template soInstanceUnitFullProperty<soTurnEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 2>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 2>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 2>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 2>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 2>::capacity() const;
template soInstanceUnitFullProperty<soTurnEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 2>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 2>::setSize(s32);
