#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soOtherAnim.h>

template s32 soArrayVector<soOtherAnim, 3>::getTopIndex() const;
template void soArrayVector<soOtherAnim, 3>::setTopIndex(s32);
template s32 soArrayVector<soOtherAnim, 3>::getLastIndex() const;
template void soArrayVector<soOtherAnim, 3>::setLastIndex(s32);
template soOtherAnim& soArrayVector<soOtherAnim, 3>::getArrayValueConst(s32);
template void soArrayVector<soOtherAnim, 3>::onFull();
template void soArrayVector<soOtherAnim, 3>::offFull();
template bool soArrayVector<soOtherAnim, 3>::isFull() const;
template s32 soArrayVector<soOtherAnim, 3>::capacity() const;
template s32 soArrayVector<soOtherAnim, 3>::size() const;
template void soArrayVector<soOtherAnim, 3>::setSize(s32);
