#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soKineticEnergy;

template soInstanceUnitFullProperty<soKineticEnergy*>& soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::at(s32);
template soInstanceUnitFullProperty<soKineticEnergy*> const& soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::at(s32) const;
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::unshift(soInstanceUnitFullProperty<soKineticEnergy*> const&);
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::shift();
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::push(soInstanceUnitFullProperty<soKineticEnergy*> const&);
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::pop();
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::insert(s32,soInstanceUnitFullProperty<soKineticEnergy*> const&);
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::erase(s32);
template s32 soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::size() const;
template bool soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::isFull() const;
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::set(s32,soInstanceUnitFullProperty<soKineticEnergy*> const&,s32);
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::clear();
template s32 soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::capacity() const;
template bool soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::isNull() const;
template s32 soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::shiftFreeArrayIndex(s32);
template s32 soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::getArrayIndex(s32) const;
template s32 soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::insertSub(s32,s32);
template void soArrayList<soInstanceUnitFullProperty<soKineticEnergy*>, 10>::eraseSub(s32);
