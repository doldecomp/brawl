#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_area_instance.h>

template s32 soArrayVector<soAreaInstance, 8>::getTopIndex() const;
template void soArrayVector<soAreaInstance, 8>::setTopIndex(s32);
template s32 soArrayVector<soAreaInstance, 8>::getLastIndex() const;
template void soArrayVector<soAreaInstance, 8>::setLastIndex(s32);
template soAreaInstance& soArrayVector<soAreaInstance, 8>::getArrayValueConst(s32);
template void soArrayVector<soAreaInstance, 8>::onFull();
template void soArrayVector<soAreaInstance, 8>::offFull();
template bool soArrayVector<soAreaInstance, 8>::isFull() const;
template s32 soArrayVector<soAreaInstance, 8>::capacity() const;
template s32 soArrayVector<soAreaInstance, 8>::size() const;
template void soArrayVector<soAreaInstance, 8>::setSize(s32);
