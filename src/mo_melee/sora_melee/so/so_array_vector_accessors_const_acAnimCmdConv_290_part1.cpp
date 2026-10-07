#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 290>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 290>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 290>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 290>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 290>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 290>::onFull();
template void soArrayVector<const acAnimCmdConv*, 290>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 290>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 290>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 290>::size() const;
template void soArrayVector<const acAnimCmdConv*, 290>::setSize(s32);
