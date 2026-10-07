#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 288>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 288>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 288>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 288>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 288>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 288>::onFull();
template void soArrayVector<const acAnimCmdConv*, 288>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 288>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 288>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 288>::size() const;
template void soArrayVector<const acAnimCmdConv*, 288>::setSize(s32);
