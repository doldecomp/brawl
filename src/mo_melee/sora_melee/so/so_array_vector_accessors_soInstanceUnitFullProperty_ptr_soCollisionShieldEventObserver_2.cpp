#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionShieldEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 2>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 2>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 2>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 2>::setLastIndex(s32);
template soInstanceUnitFullProperty<soCollisionShieldEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 2>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 2>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 2>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 2>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 2>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 2>::size() const;
template soInstanceUnitFullProperty<soCollisionShieldEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 2>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 2>::setSize(s32);
