#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionReflectorEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 4>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 4>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 4>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 4>::setLastIndex(s32);
template soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 4>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 4>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 4>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 4>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 4>::capacity() const;
template soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 4>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 4>::setSize(s32);
