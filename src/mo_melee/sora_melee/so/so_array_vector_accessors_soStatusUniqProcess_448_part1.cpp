#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 448>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 448>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 448>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 448>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 448>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 448>::onFull();
template void soArrayVector<soStatusUniqProcess*, 448>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 448>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 448>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 448>::size() const;
template void soArrayVector<soStatusUniqProcess*, 448>::setSize(s32);
