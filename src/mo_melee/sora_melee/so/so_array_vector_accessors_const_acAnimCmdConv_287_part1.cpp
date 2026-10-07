#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 287>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 287>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 287>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 287>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 287>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 287>::onFull();
template void soArrayVector<const acAnimCmdConv*, 287>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 287>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 287>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 287>::size() const;
template void soArrayVector<const acAnimCmdConv*, 287>::setSize(s32);
