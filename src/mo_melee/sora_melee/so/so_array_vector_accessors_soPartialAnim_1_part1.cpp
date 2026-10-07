#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soPartialAnim.h>

template s32 soArrayVector<soPartialAnim, 1>::getTopIndex() const;
template void soArrayVector<soPartialAnim, 1>::setTopIndex(s32);
template s32 soArrayVector<soPartialAnim, 1>::getLastIndex() const;
template void soArrayVector<soPartialAnim, 1>::setLastIndex(s32);
template soPartialAnim& soArrayVector<soPartialAnim, 1>::getArrayValueConst(s32);
template void soArrayVector<soPartialAnim, 1>::onFull();
template void soArrayVector<soPartialAnim, 1>::offFull();
template bool soArrayVector<soPartialAnim, 1>::isFull() const;
template s32 soArrayVector<soPartialAnim, 1>::capacity() const;
template s32 soArrayVector<soPartialAnim, 1>::size() const;
template void soArrayVector<soPartialAnim, 1>::setSize(s32);
