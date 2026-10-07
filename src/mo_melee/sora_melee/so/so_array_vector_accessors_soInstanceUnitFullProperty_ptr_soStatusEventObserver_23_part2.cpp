#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soStatusEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 23>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 23>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 23>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 23>::setLastIndex(s32);
template soInstanceUnitFullProperty<soStatusEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 23>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 23>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 23>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 23>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 23>::capacity() const;
template soInstanceUnitFullProperty<soStatusEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 23>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 23>::setSize(s32);
