#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soAnimCmdEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 33>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 33>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 33>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 33>::setLastIndex(s32);
template soInstanceUnitFullProperty<soAnimCmdEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 33>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 33>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 33>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 33>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 33>::capacity() const;
template soInstanceUnitFullProperty<soAnimCmdEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 33>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 33>::setSize(s32);
