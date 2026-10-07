#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionHitEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionHitEventObserver*>, 2>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionHitEventObserver*>, 2>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionHitEventObserver*>, 2>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionHitEventObserver*>, 2>::setLastIndex(s32);
template soInstanceUnitFullProperty<soCollisionHitEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionHitEventObserver*>, 2>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soCollisionHitEventObserver*>, 2>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soCollisionHitEventObserver*>, 2>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soCollisionHitEventObserver*>, 2>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionHitEventObserver*>, 2>::capacity() const;
template soInstanceUnitFullProperty<soCollisionHitEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionHitEventObserver*>, 2>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionHitEventObserver*>, 2>::setSize(s32);
