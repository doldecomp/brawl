#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 305>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 305>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 305>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 305>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 305>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 305>::onFull();
template void soArrayVector<const acAnimCmdConv*, 305>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 305>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 305>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 305>::size() const;
template void soArrayVector<const acAnimCmdConv*, 305>::setSize(s32);
