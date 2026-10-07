#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soStatusEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 32>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 32>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 32>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 32>::setLastIndex(s32);
template soInstanceUnitFullProperty<soStatusEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 32>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 32>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 32>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 32>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 32>::capacity() const;
template soInstanceUnitFullProperty<soStatusEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 32>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 32>::setSize(s32);
