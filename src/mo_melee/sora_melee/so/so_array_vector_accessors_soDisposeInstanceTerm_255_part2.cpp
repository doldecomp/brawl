#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soDisposeInstanceTerm.h>

template s32 soArrayVector<soDisposeInstanceTerm, 255>::getTopIndex() const;
template void soArrayVector<soDisposeInstanceTerm, 255>::setTopIndex(s32);
template s32 soArrayVector<soDisposeInstanceTerm, 255>::getLastIndex() const;
template void soArrayVector<soDisposeInstanceTerm, 255>::setLastIndex(s32);
template soDisposeInstanceTerm& soArrayVector<soDisposeInstanceTerm, 255>::getArrayValueConst(s32);
template void soArrayVector<soDisposeInstanceTerm, 255>::onFull();
template void soArrayVector<soDisposeInstanceTerm, 255>::offFull();
template bool soArrayVector<soDisposeInstanceTerm, 255>::isFull() const;
template s32 soArrayVector<soDisposeInstanceTerm, 255>::capacity() const;
template soDisposeInstanceTerm& soArrayVector<soDisposeInstanceTerm, 255>::atFastAbstractSub(s32) const;
template void soArrayVector<soDisposeInstanceTerm, 255>::setSize(s32);
