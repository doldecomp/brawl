#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soPartialAnim.h>

template s32 soArrayVector<soPartialAnim, 2>::getTopIndex() const;
template void soArrayVector<soPartialAnim, 2>::setTopIndex(s32);
template s32 soArrayVector<soPartialAnim, 2>::getLastIndex() const;
template void soArrayVector<soPartialAnim, 2>::setLastIndex(s32);
template soPartialAnim& soArrayVector<soPartialAnim, 2>::getArrayValueConst(s32);
template void soArrayVector<soPartialAnim, 2>::onFull();
template void soArrayVector<soPartialAnim, 2>::offFull();
template bool soArrayVector<soPartialAnim, 2>::isFull() const;
template s32 soArrayVector<soPartialAnim, 2>::capacity() const;
template s32 soArrayVector<soPartialAnim, 2>::size() const;
template void soArrayVector<soPartialAnim, 2>::setSize(s32);
