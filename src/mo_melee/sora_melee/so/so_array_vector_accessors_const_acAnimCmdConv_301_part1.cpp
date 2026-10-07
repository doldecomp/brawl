#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 301>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 301>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 301>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 301>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 301>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 301>::onFull();
template void soArrayVector<const acAnimCmdConv*, 301>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 301>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 301>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 301>::size() const;
template void soArrayVector<const acAnimCmdConv*, 301>::setSize(s32);
