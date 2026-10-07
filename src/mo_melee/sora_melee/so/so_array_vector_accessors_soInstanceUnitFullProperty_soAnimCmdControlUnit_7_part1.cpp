#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
#include <so/templates/so_array_value_soAnimCmdControlUnit.h>

template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 7>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 7>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 7>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 7>::setLastIndex(s32);
template soInstanceUnitFullProperty<soAnimCmdControlUnit>& soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 7>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 7>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 7>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 7>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 7>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 7>::size() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 7>::setSize(s32);
