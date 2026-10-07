#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soDamageEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soDamageEventObserver*>, 4>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soDamageEventObserver*>, 4>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soDamageEventObserver*>, 4>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soDamageEventObserver*>, 4>::setLastIndex(s32);
template soInstanceUnitFullProperty<soDamageEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soDamageEventObserver*>, 4>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soDamageEventObserver*>, 4>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soDamageEventObserver*>, 4>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soDamageEventObserver*>, 4>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soDamageEventObserver*>, 4>::capacity() const;
template soInstanceUnitFullProperty<soDamageEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soDamageEventObserver*>, 4>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soDamageEventObserver*>, 4>::setSize(s32);
