#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soTurnEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 6>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 6>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 6>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 6>::setLastIndex(s32);
template soInstanceUnitFullProperty<soTurnEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 6>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 6>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 6>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 6>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 6>::capacity() const;
template soInstanceUnitFullProperty<soTurnEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 6>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 6>::setSize(s32);
