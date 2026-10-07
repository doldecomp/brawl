#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soTeamEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soTeamEventObserver*>, 255>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTeamEventObserver*>, 255>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soTeamEventObserver*>, 255>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTeamEventObserver*>, 255>::setLastIndex(s32);
template soInstanceUnitFullProperty<soTeamEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soTeamEventObserver*>, 255>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soTeamEventObserver*>, 255>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soTeamEventObserver*>, 255>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soTeamEventObserver*>, 255>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soTeamEventObserver*>, 255>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soTeamEventObserver*>, 255>::size() const;
template soInstanceUnitFullProperty<soTeamEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soTeamEventObserver*>, 255>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soTeamEventObserver*>, 255>::setSize(s32);
