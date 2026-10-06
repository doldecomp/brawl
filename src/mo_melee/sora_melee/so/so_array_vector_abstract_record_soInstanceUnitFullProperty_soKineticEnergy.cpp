#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soKineticEnergy;

template soInstanceUnitFullProperty<soKineticEnergy*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soKineticEnergy*> >::at(s32);
template const soInstanceUnitFullProperty<soKineticEnergy*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soKineticEnergy*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soKineticEnergy*> >::unshift(const soInstanceUnitFullProperty<soKineticEnergy*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soKineticEnergy*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soKineticEnergy*> >::push(const soInstanceUnitFullProperty<soKineticEnergy*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soKineticEnergy*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soKineticEnergy*> >::insert(s32, const soInstanceUnitFullProperty<soKineticEnergy*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soKineticEnergy*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soKineticEnergy*> >::set(s32, const soInstanceUnitFullProperty<soKineticEnergy*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soKineticEnergy*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soKineticEnergy*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soKineticEnergy*> >::substitution(s32, s32);
