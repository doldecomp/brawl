#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soOtherAnim.h>

template s32 soArrayVector<soOtherAnim, 2>::getTopIndex() const;
template void soArrayVector<soOtherAnim, 2>::setTopIndex(s32);
template s32 soArrayVector<soOtherAnim, 2>::getLastIndex() const;
template void soArrayVector<soOtherAnim, 2>::setLastIndex(s32);
template soOtherAnim& soArrayVector<soOtherAnim, 2>::getArrayValueConst(s32);
template void soArrayVector<soOtherAnim, 2>::onFull();
template void soArrayVector<soOtherAnim, 2>::offFull();
template bool soArrayVector<soOtherAnim, 2>::isFull() const;
template s32 soArrayVector<soOtherAnim, 2>::capacity() const;
template s32 soArrayVector<soOtherAnim, 2>::size() const;
template void soArrayVector<soOtherAnim, 2>::setSize(s32);
