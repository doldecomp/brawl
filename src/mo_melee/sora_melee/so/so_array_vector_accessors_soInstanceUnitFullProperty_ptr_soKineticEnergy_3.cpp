#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soKineticEnergy;

template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 3>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 3>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 3>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 3>::setLastIndex(s32);
template soInstanceUnitFullProperty<soKineticEnergy*>& soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 3>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 3>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 3>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 3>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 3>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 3>::size() const;
template soInstanceUnitFullProperty<soKineticEnergy*>& soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 3>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 3>::setSize(s32);
