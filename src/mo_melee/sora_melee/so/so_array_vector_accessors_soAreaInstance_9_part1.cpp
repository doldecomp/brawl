#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_area_instance.h>

template s32 soArrayVector<soAreaInstance, 9>::getTopIndex() const;
template void soArrayVector<soAreaInstance, 9>::setTopIndex(s32);
template s32 soArrayVector<soAreaInstance, 9>::getLastIndex() const;
template void soArrayVector<soAreaInstance, 9>::setLastIndex(s32);
template soAreaInstance& soArrayVector<soAreaInstance, 9>::getArrayValueConst(s32);
template void soArrayVector<soAreaInstance, 9>::onFull();
template void soArrayVector<soAreaInstance, 9>::offFull();
template bool soArrayVector<soAreaInstance, 9>::isFull() const;
template s32 soArrayVector<soAreaInstance, 9>::capacity() const;
template s32 soArrayVector<soAreaInstance, 9>::size() const;
template void soArrayVector<soAreaInstance, 9>::setSize(s32);
