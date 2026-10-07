#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soKineticEnergy;

template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 4>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 4>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 4>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 4>::setLastIndex(s32);
template soInstanceUnitFullProperty<soKineticEnergy*>& soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 4>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 4>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 4>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 4>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 4>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 4>::size() const;
template void soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 4>::setSize(s32);
