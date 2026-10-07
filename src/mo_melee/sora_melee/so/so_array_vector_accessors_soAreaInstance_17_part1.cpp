#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_area_instance.h>

template s32 soArrayVector<soAreaInstance, 17>::getTopIndex() const;
template void soArrayVector<soAreaInstance, 17>::setTopIndex(s32);
template s32 soArrayVector<soAreaInstance, 17>::getLastIndex() const;
template void soArrayVector<soAreaInstance, 17>::setLastIndex(s32);
template soAreaInstance& soArrayVector<soAreaInstance, 17>::getArrayValueConst(s32);
template void soArrayVector<soAreaInstance, 17>::onFull();
template void soArrayVector<soAreaInstance, 17>::offFull();
template bool soArrayVector<soAreaInstance, 17>::isFull() const;
template s32 soArrayVector<soAreaInstance, 17>::capacity() const;
template s32 soArrayVector<soAreaInstance, 17>::size() const;
template void soArrayVector<soAreaInstance, 17>::setSize(s32);
