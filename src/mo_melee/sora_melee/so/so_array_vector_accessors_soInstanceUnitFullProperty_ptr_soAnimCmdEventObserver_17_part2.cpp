#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soAnimCmdEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 17>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 17>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 17>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 17>::setLastIndex(s32);
template soInstanceUnitFullProperty<soAnimCmdEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 17>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 17>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 17>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 17>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 17>::capacity() const;
template soInstanceUnitFullProperty<soAnimCmdEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 17>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 17>::setSize(s32);
