#pragma force_active on
#include <so/so_array.h>

template s32 soArrayVector<float, 5>::getTopIndex() const;
template void soArrayVector<float, 5>::setTopIndex(s32);
template s32 soArrayVector<float, 5>::getLastIndex() const;
template void soArrayVector<float, 5>::setLastIndex(s32);
template float& soArrayVector<float, 5>::getArrayValueConst(s32);
template void soArrayVector<float, 5>::onFull();
template void soArrayVector<float, 5>::offFull();
template bool soArrayVector<float, 5>::isFull() const;
template s32 soArrayVector<float, 5>::capacity() const;
template s32 soArrayVector<float, 5>::size() const;
template void soArrayVector<float, 5>::setSize(s32);
