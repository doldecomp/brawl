#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_area_instance.h>

template s32 soArrayVector<soAreaInstance, 11>::getTopIndex() const;
template void soArrayVector<soAreaInstance, 11>::setTopIndex(s32);
template s32 soArrayVector<soAreaInstance, 11>::getLastIndex() const;
template void soArrayVector<soAreaInstance, 11>::setLastIndex(s32);
template soAreaInstance& soArrayVector<soAreaInstance, 11>::getArrayValueConst(s32);
template void soArrayVector<soAreaInstance, 11>::onFull();
template void soArrayVector<soAreaInstance, 11>::offFull();
template bool soArrayVector<soAreaInstance, 11>::isFull() const;
template s32 soArrayVector<soAreaInstance, 11>::capacity() const;
template s32 soArrayVector<soAreaInstance, 11>::size() const;
template void soArrayVector<soAreaInstance, 11>::setSize(s32);
