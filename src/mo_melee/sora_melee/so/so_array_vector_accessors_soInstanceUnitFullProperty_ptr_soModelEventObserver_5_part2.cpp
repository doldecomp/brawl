#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soModelEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 5>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 5>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 5>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 5>::setLastIndex(s32);
template soInstanceUnitFullProperty<soModelEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 5>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 5>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 5>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 5>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 5>::capacity() const;
template soInstanceUnitFullProperty<soModelEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 5>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 5>::setSize(s32);
