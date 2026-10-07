#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soKineticEnergy;

template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 12>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 12>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 12>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 12>::setLastIndex(s32);
template soInstanceUnitFullProperty<soKineticEnergy*>& soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 12>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 12>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 12>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 12>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 12>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 12>::size() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 12>::setSize(s32);
