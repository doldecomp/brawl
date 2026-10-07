#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionAttackEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 2>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 2>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 2>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 2>::setLastIndex(s32);
template soInstanceUnitFullProperty<soCollisionAttackEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 2>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 2>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 2>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 2>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 2>::capacity() const;
template soInstanceUnitFullProperty<soCollisionAttackEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 2>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 2>::setSize(s32);
