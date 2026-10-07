#pragma force_active on
#include <so/so_array.h>

template s32 soArrayVector<u32, 5>::getTopIndex() const;
template void soArrayVector<u32, 5>::setTopIndex(s32);
template s32 soArrayVector<u32, 5>::getLastIndex() const;
template void soArrayVector<u32, 5>::setLastIndex(s32);
template u32& soArrayVector<u32, 5>::getArrayValueConst(s32);
template void soArrayVector<u32, 5>::onFull();
template void soArrayVector<u32, 5>::offFull();
template bool soArrayVector<u32, 5>::isFull() const;
template s32 soArrayVector<u32, 5>::capacity() const;
template s32 soArrayVector<u32, 5>::size() const;
template void soArrayVector<u32, 5>::setSize(s32);
