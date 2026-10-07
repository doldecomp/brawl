#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 285>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 285>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 285>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 285>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 285>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 285>::onFull();
template void soArrayVector<const acAnimCmdConv*, 285>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 285>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 285>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 285>::size() const;
template void soArrayVector<const acAnimCmdConv*, 285>::setSize(s32);
