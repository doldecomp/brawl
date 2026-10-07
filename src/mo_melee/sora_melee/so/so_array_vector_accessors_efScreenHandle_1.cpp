#pragma force_active on
#include <so/so_array.h>
#include <ef/ef_screen_handle.h>

template s32 soArrayVector<efScreenHandle, 1>::getTopIndex() const;
template void soArrayVector<efScreenHandle, 1>::setTopIndex(s32);
template s32 soArrayVector<efScreenHandle, 1>::getLastIndex() const;
template void soArrayVector<efScreenHandle, 1>::setLastIndex(s32);
template efScreenHandle& soArrayVector<efScreenHandle, 1>::getArrayValueConst(s32);
template void soArrayVector<efScreenHandle, 1>::onFull();
template void soArrayVector<efScreenHandle, 1>::offFull();
template bool soArrayVector<efScreenHandle, 1>::isFull() const;
template s32 soArrayVector<efScreenHandle, 1>::capacity() const;
template s32 soArrayVector<efScreenHandle, 1>::size() const;
template efScreenHandle& soArrayVector<efScreenHandle, 1>::atFastAbstractSub(s32) const;
template void soArrayVector<efScreenHandle, 1>::setSize(s32);
