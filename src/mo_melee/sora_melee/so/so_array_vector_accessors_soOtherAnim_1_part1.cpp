#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soOtherAnim.h>

template s32 soArrayVector<soOtherAnim, 1>::getTopIndex() const;
template void soArrayVector<soOtherAnim, 1>::setTopIndex(s32);
template s32 soArrayVector<soOtherAnim, 1>::getLastIndex() const;
template void soArrayVector<soOtherAnim, 1>::setLastIndex(s32);
template soOtherAnim& soArrayVector<soOtherAnim, 1>::getArrayValueConst(s32);
template void soArrayVector<soOtherAnim, 1>::onFull();
template void soArrayVector<soOtherAnim, 1>::offFull();
template bool soArrayVector<soOtherAnim, 1>::isFull() const;
template s32 soArrayVector<soOtherAnim, 1>::capacity() const;
template s32 soArrayVector<soOtherAnim, 1>::size() const;
template void soArrayVector<soOtherAnim, 1>::setSize(s32);
