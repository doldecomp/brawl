#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_area_instance.h>

template s32 soArrayVector<soAreaInstance, 15>::getTopIndex() const;
template void soArrayVector<soAreaInstance, 15>::setTopIndex(s32);
template s32 soArrayVector<soAreaInstance, 15>::getLastIndex() const;
template void soArrayVector<soAreaInstance, 15>::setLastIndex(s32);
template soAreaInstance& soArrayVector<soAreaInstance, 15>::getArrayValueConst(s32);
template void soArrayVector<soAreaInstance, 15>::onFull();
template void soArrayVector<soAreaInstance, 15>::offFull();
template bool soArrayVector<soAreaInstance, 15>::isFull() const;
template s32 soArrayVector<soAreaInstance, 15>::capacity() const;
template s32 soArrayVector<soAreaInstance, 15>::size() const;
template void soArrayVector<soAreaInstance, 15>::setSize(s32);
