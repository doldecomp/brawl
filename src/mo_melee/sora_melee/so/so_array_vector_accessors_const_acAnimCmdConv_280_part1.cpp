#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 280>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 280>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 280>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 280>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 280>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 280>::onFull();
template void soArrayVector<const acAnimCmdConv*, 280>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 280>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 280>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 280>::size() const;
template void soArrayVector<const acAnimCmdConv*, 280>::setSize(s32);
