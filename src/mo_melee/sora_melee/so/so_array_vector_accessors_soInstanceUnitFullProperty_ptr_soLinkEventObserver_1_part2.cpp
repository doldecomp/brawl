#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soLinkEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 1>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 1>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 1>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 1>::setLastIndex(s32);
template soInstanceUnitFullProperty<soLinkEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 1>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 1>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 1>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 1>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 1>::capacity() const;
template soInstanceUnitFullProperty<soLinkEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 1>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 1>::setSize(s32);
