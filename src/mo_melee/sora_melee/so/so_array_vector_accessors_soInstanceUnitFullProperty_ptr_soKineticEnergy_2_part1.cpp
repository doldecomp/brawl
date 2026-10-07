#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soKineticEnergy;

template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 2>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 2>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 2>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 2>::setLastIndex(s32);
template soInstanceUnitFullProperty<soKineticEnergy*>& soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 2>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 2>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 2>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 2>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 2>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 2>::size() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 2>::setSize(s32);
