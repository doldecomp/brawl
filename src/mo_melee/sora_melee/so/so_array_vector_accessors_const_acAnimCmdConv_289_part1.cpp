#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 289>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 289>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 289>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 289>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 289>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 289>::onFull();
template void soArrayVector<const acAnimCmdConv*, 289>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 289>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 289>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 289>::size() const;
template void soArrayVector<const acAnimCmdConv*, 289>::setSize(s32);
