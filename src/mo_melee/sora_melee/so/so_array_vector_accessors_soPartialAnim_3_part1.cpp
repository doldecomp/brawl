#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soPartialAnim.h>

template s32 soArrayVector<soPartialAnim, 3>::getTopIndex() const;
template void soArrayVector<soPartialAnim, 3>::setTopIndex(s32);
template s32 soArrayVector<soPartialAnim, 3>::getLastIndex() const;
template void soArrayVector<soPartialAnim, 3>::setLastIndex(s32);
template soPartialAnim& soArrayVector<soPartialAnim, 3>::getArrayValueConst(s32);
template void soArrayVector<soPartialAnim, 3>::onFull();
template void soArrayVector<soPartialAnim, 3>::offFull();
template bool soArrayVector<soPartialAnim, 3>::isFull() const;
template s32 soArrayVector<soPartialAnim, 3>::capacity() const;
template s32 soArrayVector<soPartialAnim, 3>::size() const;
template void soArrayVector<soPartialAnim, 3>::setSize(s32);
