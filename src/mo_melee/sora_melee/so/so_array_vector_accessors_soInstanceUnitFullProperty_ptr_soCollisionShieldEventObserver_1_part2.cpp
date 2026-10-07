#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionShieldEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 1>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 1>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 1>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 1>::setLastIndex(s32);
template soInstanceUnitFullProperty<soCollisionShieldEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 1>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 1>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 1>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 1>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 1>::capacity() const;
template soInstanceUnitFullProperty<soCollisionShieldEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 1>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 1>::setSize(s32);
