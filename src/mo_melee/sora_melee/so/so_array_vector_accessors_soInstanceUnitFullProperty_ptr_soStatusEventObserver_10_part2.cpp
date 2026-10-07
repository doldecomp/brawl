#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soStatusEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 10>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 10>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 10>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 10>::setLastIndex(s32);
template soInstanceUnitFullProperty<soStatusEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 10>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 10>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 10>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 10>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 10>::capacity() const;
template soInstanceUnitFullProperty<soStatusEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 10>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 10>::setSize(s32);
