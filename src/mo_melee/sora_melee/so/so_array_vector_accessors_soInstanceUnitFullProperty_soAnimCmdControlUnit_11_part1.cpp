#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
#include <so/templates/so_array_value_soAnimCmdControlUnit.h>

template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::setLastIndex(s32);
template soInstanceUnitFullProperty<soAnimCmdControlUnit>& soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::size() const;
template void soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11>::setSize(s32);
