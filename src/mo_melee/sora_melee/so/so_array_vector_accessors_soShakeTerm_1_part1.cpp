#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soShakeTerm.h>

template s32 soArrayVector<soShakeTerm, 1>::getTopIndex() const;
template void soArrayVector<soShakeTerm, 1>::setTopIndex(s32);
template s32 soArrayVector<soShakeTerm, 1>::getLastIndex() const;
template void soArrayVector<soShakeTerm, 1>::setLastIndex(s32);
template soShakeTerm& soArrayVector<soShakeTerm, 1>::getArrayValueConst(s32);
template void soArrayVector<soShakeTerm, 1>::onFull();
template void soArrayVector<soShakeTerm, 1>::offFull();
template bool soArrayVector<soShakeTerm, 1>::isFull() const;
template s32 soArrayVector<soShakeTerm, 1>::capacity() const;
template s32 soArrayVector<soShakeTerm, 1>::size() const;
template void soArrayVector<soShakeTerm, 1>::setSize(s32);
