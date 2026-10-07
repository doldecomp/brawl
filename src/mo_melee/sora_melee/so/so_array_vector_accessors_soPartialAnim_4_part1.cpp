#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soPartialAnim.h>

template s32 soArrayVector<soPartialAnim, 4>::getTopIndex() const;
template void soArrayVector<soPartialAnim, 4>::setTopIndex(s32);
template s32 soArrayVector<soPartialAnim, 4>::getLastIndex() const;
template void soArrayVector<soPartialAnim, 4>::setLastIndex(s32);
template soPartialAnim& soArrayVector<soPartialAnim, 4>::getArrayValueConst(s32);
template void soArrayVector<soPartialAnim, 4>::onFull();
template void soArrayVector<soPartialAnim, 4>::offFull();
template bool soArrayVector<soPartialAnim, 4>::isFull() const;
template s32 soArrayVector<soPartialAnim, 4>::capacity() const;
template s32 soArrayVector<soPartialAnim, 4>::size() const;
template void soArrayVector<soPartialAnim, 4>::setSize(s32);
