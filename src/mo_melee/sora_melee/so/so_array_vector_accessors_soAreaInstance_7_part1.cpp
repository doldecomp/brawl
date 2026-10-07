#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_area_instance.h>

template s32 soArrayVector<soAreaInstance, 7>::getTopIndex() const;
template void soArrayVector<soAreaInstance, 7>::setTopIndex(s32);
template s32 soArrayVector<soAreaInstance, 7>::getLastIndex() const;
template void soArrayVector<soAreaInstance, 7>::setLastIndex(s32);
template soAreaInstance& soArrayVector<soAreaInstance, 7>::getArrayValueConst(s32);
template void soArrayVector<soAreaInstance, 7>::onFull();
template void soArrayVector<soAreaInstance, 7>::offFull();
template bool soArrayVector<soAreaInstance, 7>::isFull() const;
template s32 soArrayVector<soAreaInstance, 7>::capacity() const;
template s32 soArrayVector<soAreaInstance, 7>::size() const;
template void soArrayVector<soAreaInstance, 7>::setSize(s32);
