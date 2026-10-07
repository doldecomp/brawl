#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soStatusEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 12>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 12>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 12>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 12>::setLastIndex(s32);
template soInstanceUnitFullProperty<soStatusEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 12>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 12>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 12>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 12>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 12>::capacity() const;
template soInstanceUnitFullProperty<soStatusEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 12>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 12>::setSize(s32);
