#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soMotionEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soMotionEventObserver*>, 1>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soMotionEventObserver*>, 1>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soMotionEventObserver*>, 1>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soMotionEventObserver*>, 1>::setLastIndex(s32);
template soInstanceUnitFullProperty<soMotionEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soMotionEventObserver*>, 1>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soMotionEventObserver*>, 1>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soMotionEventObserver*>, 1>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soMotionEventObserver*>, 1>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soMotionEventObserver*>, 1>::capacity() const;
template soInstanceUnitFullProperty<soMotionEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soMotionEventObserver*>, 1>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soMotionEventObserver*>, 1>::setSize(s32);
