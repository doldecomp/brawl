#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionAttackEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 3>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 3>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 3>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 3>::setLastIndex(s32);
template soInstanceUnitFullProperty<soCollisionAttackEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 3>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 3>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 3>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 3>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 3>::capacity() const;
template soInstanceUnitFullProperty<soCollisionAttackEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 3>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 3>::setSize(s32);
