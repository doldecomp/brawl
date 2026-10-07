#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 303>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 303>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 303>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 303>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 303>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 303>::onFull();
template void soArrayVector<const acAnimCmdConv*, 303>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 303>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 303>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 303>::size() const;
template void soArrayVector<const acAnimCmdConv*, 303>::setSize(s32);
