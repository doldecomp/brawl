#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
#include <so/templates/so_array_value_soTransitionTerm.h>

template s32 soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 17>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 17>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 17>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 17>::setLastIndex(s32);
template soInstanceUnitFullProperty<soTransitionTerm>& soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 17>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 17>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 17>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 17>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 17>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 17>::size() const;
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 17>::setSize(s32);
