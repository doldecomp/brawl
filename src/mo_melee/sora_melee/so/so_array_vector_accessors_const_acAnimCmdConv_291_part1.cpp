#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 291>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 291>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 291>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 291>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 291>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 291>::onFull();
template void soArrayVector<const acAnimCmdConv*, 291>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 291>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 291>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 291>::size() const;
template void soArrayVector<const acAnimCmdConv*, 291>::setSize(s32);
