#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soTurnEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 7>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 7>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 7>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 7>::setLastIndex(s32);
template soInstanceUnitFullProperty<soTurnEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 7>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 7>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 7>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 7>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 7>::capacity() const;
template soInstanceUnitFullProperty<soTurnEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 7>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 7>::setSize(s32);
