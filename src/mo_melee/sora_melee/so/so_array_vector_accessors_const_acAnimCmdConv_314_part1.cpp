#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 314>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 314>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 314>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 314>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 314>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 314>::onFull();
template void soArrayVector<const acAnimCmdConv*, 314>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 314>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 314>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 314>::size() const;
template void soArrayVector<const acAnimCmdConv*, 314>::setSize(s32);
