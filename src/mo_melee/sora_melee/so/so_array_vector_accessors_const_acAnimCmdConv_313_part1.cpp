#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 313>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 313>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 313>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 313>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 313>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 313>::onFull();
template void soArrayVector<const acAnimCmdConv*, 313>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 313>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 313>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 313>::size() const;
template void soArrayVector<const acAnimCmdConv*, 313>::setSize(s32);
