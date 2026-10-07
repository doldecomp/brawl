#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class ftOutsideEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<ftOutsideEventObserver*>, 8>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<ftOutsideEventObserver*>, 8>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<ftOutsideEventObserver*>, 8>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<ftOutsideEventObserver*>, 8>::setLastIndex(s32);
template soInstanceUnitFullProperty<ftOutsideEventObserver*>& soArrayVector<soInstanceUnitFullProperty<ftOutsideEventObserver*>, 8>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<ftOutsideEventObserver*>, 8>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<ftOutsideEventObserver*>, 8>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<ftOutsideEventObserver*>, 8>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<ftOutsideEventObserver*>, 8>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<ftOutsideEventObserver*>, 8>::size() const;
template soInstanceUnitFullProperty<ftOutsideEventObserver*>& soArrayVector<soInstanceUnitFullProperty<ftOutsideEventObserver*>, 8>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<ftOutsideEventObserver*>, 8>::setSize(s32);
