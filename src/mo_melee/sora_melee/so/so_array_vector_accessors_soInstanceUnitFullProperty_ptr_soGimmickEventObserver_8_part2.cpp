#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soGimmickEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 8>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 8>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 8>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 8>::setLastIndex(s32);
template soInstanceUnitFullProperty<soGimmickEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 8>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 8>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 8>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 8>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 8>::capacity() const;
template soInstanceUnitFullProperty<soGimmickEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 8>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 8>::setSize(s32);
