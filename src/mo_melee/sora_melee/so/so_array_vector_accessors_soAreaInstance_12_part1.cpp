#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_area_instance.h>

template s32 soArrayVector<soAreaInstance, 12>::getTopIndex() const;
template void soArrayVector<soAreaInstance, 12>::setTopIndex(s32);
template s32 soArrayVector<soAreaInstance, 12>::getLastIndex() const;
template void soArrayVector<soAreaInstance, 12>::setLastIndex(s32);
template soAreaInstance& soArrayVector<soAreaInstance, 12>::getArrayValueConst(s32);
template void soArrayVector<soAreaInstance, 12>::onFull();
template void soArrayVector<soAreaInstance, 12>::offFull();
template bool soArrayVector<soAreaInstance, 12>::isFull() const;
template s32 soArrayVector<soAreaInstance, 12>::capacity() const;
template s32 soArrayVector<soAreaInstance, 12>::size() const;
template void soArrayVector<soAreaInstance, 12>::setSize(s32);
