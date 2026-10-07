#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_area_instance.h>

template s32 soArrayVector<soAreaInstance, 13>::getTopIndex() const;
template void soArrayVector<soAreaInstance, 13>::setTopIndex(s32);
template s32 soArrayVector<soAreaInstance, 13>::getLastIndex() const;
template void soArrayVector<soAreaInstance, 13>::setLastIndex(s32);
template soAreaInstance& soArrayVector<soAreaInstance, 13>::getArrayValueConst(s32);
template void soArrayVector<soAreaInstance, 13>::onFull();
template void soArrayVector<soAreaInstance, 13>::offFull();
template bool soArrayVector<soAreaInstance, 13>::isFull() const;
template s32 soArrayVector<soAreaInstance, 13>::capacity() const;
template s32 soArrayVector<soAreaInstance, 13>::size() const;
template void soArrayVector<soAreaInstance, 13>::setSize(s32);
