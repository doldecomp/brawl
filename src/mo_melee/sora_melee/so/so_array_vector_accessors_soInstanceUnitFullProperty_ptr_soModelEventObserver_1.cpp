#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soModelEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 1>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 1>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 1>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 1>::setLastIndex(s32);
template soInstanceUnitFullProperty<soModelEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 1>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 1>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 1>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 1>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 1>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 1>::size() const;
template soInstanceUnitFullProperty<soModelEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 1>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 1>::setSize(s32);
