#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
#include <so/templates/so_array_value_soTransitionTerm.h>

template s32 soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 1>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 1>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 1>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 1>::setLastIndex(s32);
template soInstanceUnitFullProperty<soTransitionTerm>& soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 1>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 1>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 1>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 1>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 1>::capacity() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 1>::size() const;
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 1>::setSize(s32);
