#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 281>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 281>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 281>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 281>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 281>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 281>::onFull();
template void soArrayVector<const acAnimCmdConv*, 281>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 281>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 281>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 281>::size() const;
template void soArrayVector<const acAnimCmdConv*, 281>::setSize(s32);
