#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 448>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 448>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 448>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 448>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 448>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 448>::onFull();
template void soArrayVector<const acAnimCmdConv*, 448>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 448>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 448>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 448>::size() const;
template void soArrayVector<const acAnimCmdConv*, 448>::setSize(s32);
