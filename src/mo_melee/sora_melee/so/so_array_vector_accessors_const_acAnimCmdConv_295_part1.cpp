#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 295>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 295>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 295>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 295>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 295>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 295>::onFull();
template void soArrayVector<const acAnimCmdConv*, 295>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 295>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 295>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 295>::size() const;
template void soArrayVector<const acAnimCmdConv*, 295>::setSize(s32);
