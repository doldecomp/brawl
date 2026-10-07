#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soShakeTerm.h>

template s32 soArrayVector<soShakeTerm, 2>::getTopIndex() const;
template void soArrayVector<soShakeTerm, 2>::setTopIndex(s32);
template s32 soArrayVector<soShakeTerm, 2>::getLastIndex() const;
template void soArrayVector<soShakeTerm, 2>::setLastIndex(s32);
template soShakeTerm& soArrayVector<soShakeTerm, 2>::getArrayValueConst(s32);
template void soArrayVector<soShakeTerm, 2>::onFull();
template void soArrayVector<soShakeTerm, 2>::offFull();
template bool soArrayVector<soShakeTerm, 2>::isFull() const;
template s32 soArrayVector<soShakeTerm, 2>::capacity() const;
template s32 soArrayVector<soShakeTerm, 2>::size() const;
template void soArrayVector<soShakeTerm, 2>::setSize(s32);
