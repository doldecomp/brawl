#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soAnimCmdEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 20>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 20>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 20>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 20>::setLastIndex(s32);
template soInstanceUnitFullProperty<soAnimCmdEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 20>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 20>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 20>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 20>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 20>::capacity() const;
template soInstanceUnitFullProperty<soAnimCmdEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 20>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdEventObserver*>, 20>::setSize(s32);
