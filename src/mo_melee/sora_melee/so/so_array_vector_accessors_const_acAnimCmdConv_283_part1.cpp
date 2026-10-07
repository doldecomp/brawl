#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 283>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 283>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 283>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 283>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 283>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 283>::onFull();
template void soArrayVector<const acAnimCmdConv*, 283>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 283>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 283>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 283>::size() const;
template void soArrayVector<const acAnimCmdConv*, 283>::setSize(s32);
