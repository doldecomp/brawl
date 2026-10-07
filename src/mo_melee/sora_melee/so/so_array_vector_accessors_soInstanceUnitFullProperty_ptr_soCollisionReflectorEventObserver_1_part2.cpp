#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionReflectorEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 1>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 1>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 1>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 1>::setLastIndex(s32);
template soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 1>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 1>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 1>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 1>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 1>::capacity() const;
template soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 1>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 1>::setSize(s32);
