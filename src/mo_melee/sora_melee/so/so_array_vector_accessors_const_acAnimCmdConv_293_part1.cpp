#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 293>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 293>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 293>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 293>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 293>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 293>::onFull();
template void soArrayVector<const acAnimCmdConv*, 293>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 293>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 293>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 293>::size() const;
template void soArrayVector<const acAnimCmdConv*, 293>::setSize(s32);
