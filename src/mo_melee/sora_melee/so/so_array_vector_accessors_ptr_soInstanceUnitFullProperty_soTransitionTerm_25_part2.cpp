#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
#include <so/templates/so_array_value_soTransitionTerm.h>

template s32 soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>*, 25>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>*, 25>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>*, 25>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>*, 25>::setLastIndex(s32);
template soInstanceUnitFullProperty<soTransitionTerm>*& soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>*, 25>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>*, 25>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>*, 25>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>*, 25>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>*, 25>::capacity() const;
template soInstanceUnitFullProperty<soTransitionTerm>*& soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>*, 25>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>*, 25>::setSize(s32);
