#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 309>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 309>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 309>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 309>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 309>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 309>::onFull();
template void soArrayVector<const acAnimCmdConv*, 309>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 309>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 309>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 309>::size() const;
template void soArrayVector<const acAnimCmdConv*, 309>::setSize(s32);
