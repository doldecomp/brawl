#pragma force_active on
#include <so/so_array.h>
class acAnimCmdConv;

template s32 soArrayVector<const acAnimCmdConv*, 299>::getTopIndex() const;
template void soArrayVector<const acAnimCmdConv*, 299>::setTopIndex(s32);
template s32 soArrayVector<const acAnimCmdConv*, 299>::getLastIndex() const;
template void soArrayVector<const acAnimCmdConv*, 299>::setLastIndex(s32);
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 299>::getArrayValueConst(s32);
template void soArrayVector<const acAnimCmdConv*, 299>::onFull();
template void soArrayVector<const acAnimCmdConv*, 299>::offFull();
template bool soArrayVector<const acAnimCmdConv*, 299>::isFull() const;
template s32 soArrayVector<const acAnimCmdConv*, 299>::capacity() const;
template s32 soArrayVector<const acAnimCmdConv*, 299>::size() const;
template const acAnimCmdConv*& soArrayVector<const acAnimCmdConv*, 299>::atFastAbstractSub(s32) const;
template void soArrayVector<const acAnimCmdConv*, 299>::setSize(s32);
