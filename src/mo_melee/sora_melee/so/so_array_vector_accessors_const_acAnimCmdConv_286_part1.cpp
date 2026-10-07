#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 286>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 286>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 286>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 286>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 286>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 286>::onFull();
template void soArrayVector<const acAnimCmdConv*, 286>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 286>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 286>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 286>::size() const;
template void soArrayVector<const acAnimCmdConv*, 286>::setSize(s32);
