#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soLinkEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 2>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 2>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 2>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 2>::setLastIndex(s32);
template soInstanceUnitFullProperty<soLinkEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 2>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 2>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 2>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 2>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 2>::capacity() const;
template soInstanceUnitFullProperty<soLinkEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 2>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 2>::setSize(s32);
