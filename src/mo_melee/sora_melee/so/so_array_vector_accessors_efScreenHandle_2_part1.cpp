#pragma force_active on
#include <so/so_array.h>
#include <ef/ef_screen_handle.h>

template s32 soArrayVector<efScreenHandle, 2>::getTopIndex() const;
template void soArrayVector<efScreenHandle, 2>::setTopIndex(s32);
template s32 soArrayVector<efScreenHandle, 2>::getLastIndex() const;
template void soArrayVector<efScreenHandle, 2>::setLastIndex(s32);
template efScreenHandle& soArrayVector<efScreenHandle, 2>::getArrayValueConst(s32);
template void soArrayVector<efScreenHandle, 2>::onFull();
template void soArrayVector<efScreenHandle, 2>::offFull();
template bool soArrayVector<efScreenHandle, 2>::isFull() const;
template s32 soArrayVector<efScreenHandle, 2>::capacity() const;
template s32 soArrayVector<efScreenHandle, 2>::size() const;
template void soArrayVector<efScreenHandle, 2>::setSize(s32);
