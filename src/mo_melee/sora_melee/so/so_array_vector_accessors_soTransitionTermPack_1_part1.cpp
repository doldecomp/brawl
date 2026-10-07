#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soTransitionTermPack.h>

template s32 soArrayVector<soTransitionTermPack, 1>::getTopIndex() const;
template void soArrayVector<soTransitionTermPack, 1>::setTopIndex(s32);
template s32 soArrayVector<soTransitionTermPack, 1>::getLastIndex() const;
template void soArrayVector<soTransitionTermPack, 1>::setLastIndex(s32);
template soTransitionTermPack& soArrayVector<soTransitionTermPack, 1>::getArrayValueConst(s32);
template void soArrayVector<soTransitionTermPack, 1>::onFull();
template void soArrayVector<soTransitionTermPack, 1>::offFull();
template bool soArrayVector<soTransitionTermPack, 1>::isFull() const;
template s32 soArrayVector<soTransitionTermPack, 1>::capacity() const;
template s32 soArrayVector<soTransitionTermPack, 1>::size() const;
template void soArrayVector<soTransitionTermPack, 1>::setSize(s32);
