#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soAnimCmdEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 32>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 32>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 32>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 32>::setLastIndex(s32);
template soInstanceUnitFullProperty<soAnimCmdEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 32>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 32>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 32>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 32>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 32>::capacity() const;
template soInstanceUnitFullProperty<soAnimCmdEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 32>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 32>::setSize(s32);
