#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_area_instance.h>

template s32 soArrayVector<soAreaInstance, 10>::getTopIndex() const;
template void soArrayVector<soAreaInstance, 10>::setTopIndex(s32);
template s32 soArrayVector<soAreaInstance, 10>::getLastIndex() const;
template void soArrayVector<soAreaInstance, 10>::setLastIndex(s32);
template soAreaInstance& soArrayVector<soAreaInstance, 10>::getArrayValueConst(s32);
template void soArrayVector<soAreaInstance, 10>::onFull();
template void soArrayVector<soAreaInstance, 10>::offFull();
template bool soArrayVector<soAreaInstance, 10>::isFull() const;
template s32 soArrayVector<soAreaInstance, 10>::capacity() const;
template s32 soArrayVector<soAreaInstance, 10>::size() const;
template void soArrayVector<soAreaInstance, 10>::setSize(s32);
