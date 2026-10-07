#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 284>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 284>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 284>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 284>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 284>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 284>::onFull();
template void soArrayVector<const acAnimCmdConv*, 284>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 284>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 284>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 284>::size() const;
template void soArrayVector<const acAnimCmdConv*, 284>::setSize(s32);
