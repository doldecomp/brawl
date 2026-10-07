#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soLogEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soLogEventObserver*>, 1>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soLogEventObserver*>, 1>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soLogEventObserver*>, 1>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soLogEventObserver*>, 1>::setLastIndex(s32);
template soInstanceUnitFullProperty<soLogEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soLogEventObserver*>, 1>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soLogEventObserver*>, 1>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soLogEventObserver*>, 1>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soLogEventObserver*>, 1>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soLogEventObserver*>, 1>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soLogEventObserver*>, 1>::size() const;
template soInstanceUnitFullProperty<soLogEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soLogEventObserver*>, 1>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soLogEventObserver*>, 1>::setSize(s32);
