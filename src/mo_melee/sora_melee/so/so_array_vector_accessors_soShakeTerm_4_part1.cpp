#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soShakeTerm.h>

template s32 soArrayVector<soShakeTerm, 4>::getTopIndex() const;
template void soArrayVector<soShakeTerm, 4>::setTopIndex(s32);
template s32 soArrayVector<soShakeTerm, 4>::getLastIndex() const;
template void soArrayVector<soShakeTerm, 4>::setLastIndex(s32);
template soShakeTerm& soArrayVector<soShakeTerm, 4>::getArrayValueConst(s32);
template void soArrayVector<soShakeTerm, 4>::onFull();
template void soArrayVector<soShakeTerm, 4>::offFull();
template bool soArrayVector<soShakeTerm, 4>::isFull() const;
template s32 soArrayVector<soShakeTerm, 4>::capacity() const;
template s32 soArrayVector<soShakeTerm, 4>::size() const;
template void soArrayVector<soShakeTerm, 4>::setSize(s32);
