#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soGimmickEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 9>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 9>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 9>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 9>::setLastIndex(s32);
template soInstanceUnitFullProperty<soGimmickEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 9>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 9>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 9>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 9>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 9>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 9>::size() const;
template soInstanceUnitFullProperty<soGimmickEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 9>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soGimmickEventObserver*>, 9>::setSize(s32);
