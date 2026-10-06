#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
#include <so/templates/so_array_value_soAnimCmdControlUnit.h>


template soInstanceUnitFullProperty<soAnimCmdControlUnit>& soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdControlUnit> >::at(s32);
template const soInstanceUnitFullProperty<soAnimCmdControlUnit>& soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdControlUnit> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdControlUnit> >::unshift(const soInstanceUnitFullProperty<soAnimCmdControlUnit>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdControlUnit> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdControlUnit> >::push(const soInstanceUnitFullProperty<soAnimCmdControlUnit>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdControlUnit> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdControlUnit> >::insert(s32, const soInstanceUnitFullProperty<soAnimCmdControlUnit>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdControlUnit> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdControlUnit> >::set(s32, const soInstanceUnitFullProperty<soAnimCmdControlUnit>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdControlUnit> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdControlUnit> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdControlUnit> >::substitution(s32, s32);
