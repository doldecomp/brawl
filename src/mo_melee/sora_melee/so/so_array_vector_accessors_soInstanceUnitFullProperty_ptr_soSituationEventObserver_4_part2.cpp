#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soSituationEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soSituationEventObserver*>, 4>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soSituationEventObserver*>, 4>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soSituationEventObserver*>, 4>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soSituationEventObserver*>, 4>::setLastIndex(s32);
template soInstanceUnitFullProperty<soSituationEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soSituationEventObserver*>, 4>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soSituationEventObserver*>, 4>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soSituationEventObserver*>, 4>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soSituationEventObserver*>, 4>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soSituationEventObserver*>, 4>::capacity() const;
template soInstanceUnitFullProperty<soSituationEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soSituationEventObserver*>, 4>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soSituationEventObserver*>, 4>::setSize(s32);
