#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soKineticEnergy;

template s32 soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::size() const;
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::clear();
template s32 soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::capacity() const;
template s32 soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::insertSub(s32,s32);
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::eraseSub(s32);
template soInstanceUnitFullProperty<soKineticEnergy*>& soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::at(s32);
template soInstanceUnitFullProperty<soKineticEnergy*> const& soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::at(s32) const;
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::unshift(soInstanceUnitFullProperty<soKineticEnergy*> const&);
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::shift();
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::push(soInstanceUnitFullProperty<soKineticEnergy*> const&);
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::pop();
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::insert(s32,soInstanceUnitFullProperty<soKineticEnergy*> const&);
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::erase(s32);
template bool soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::isFull() const;
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::set(s32,soInstanceUnitFullProperty<soKineticEnergy*> const&,s32);
template bool soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::isNull() const;
template s32 soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::shiftFreeArrayIndex(s32);
template s32 soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 11>::getArrayIndex(s32) const;
