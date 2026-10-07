#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soAnimCmdEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 7>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 7>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 7>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 7>::setLastIndex(s32);
template soInstanceUnitFullProperty<soAnimCmdEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 7>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 7>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 7>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 7>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 7>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 7>::size() const;
template soInstanceUnitFullProperty<soAnimCmdEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 7>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 7>::setSize(s32);
