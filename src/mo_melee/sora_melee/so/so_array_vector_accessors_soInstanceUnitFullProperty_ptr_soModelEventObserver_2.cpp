#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soModelEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 2>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 2>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 2>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 2>::setLastIndex(s32);
template soInstanceUnitFullProperty<soModelEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 2>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 2>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 2>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 2>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 2>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 2>::size() const;
template soInstanceUnitFullProperty<soModelEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 2>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 2>::setSize(s32);
