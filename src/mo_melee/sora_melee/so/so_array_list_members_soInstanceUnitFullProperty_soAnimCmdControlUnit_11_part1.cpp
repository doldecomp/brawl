#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
#include <so/templates/so_array_value_soAnimCmdControlUnit.h>

template soInstanceUnitFullProperty<soAnimCmdControlUnit>& soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::at(s32);
template soInstanceUnitFullProperty<soAnimCmdControlUnit> const& soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::at(s32) const;
template void soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::unshift(soInstanceUnitFullProperty<soAnimCmdControlUnit> const&);
template void soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::shift();
template void soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::push(soInstanceUnitFullProperty<soAnimCmdControlUnit> const&);
template void soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::pop();
template void soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::insert(s32,soInstanceUnitFullProperty<soAnimCmdControlUnit> const&);
template void soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::erase(s32);
template s32 soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::size() const;
template bool soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::isFull() const;
template void soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::set(s32,soInstanceUnitFullProperty<soAnimCmdControlUnit> const&,s32);
template void soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::clear();
template s32 soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::capacity() const;
template bool soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::isNull() const;
template s32 soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::shiftFreeArrayIndex(s32);
template s32 soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::getArrayIndex(s32) const;
template s32 soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::insertSub(s32,s32);
template void soArrayList<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::eraseSub(s32);
