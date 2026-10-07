#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soKineticEnergy;

template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 8>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 8>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 8>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 8>::setLastIndex(s32);
template soInstanceUnitFullProperty<soKineticEnergy*>& soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 8>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 8>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 8>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 8>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 8>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 8>::size() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 8>::setSize(s32);
