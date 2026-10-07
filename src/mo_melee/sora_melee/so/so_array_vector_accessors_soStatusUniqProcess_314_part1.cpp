#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 314>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 314>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 314>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 314>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 314>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 314>::onFull();
template void soArrayVector<soStatusUniqProcess*, 314>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 314>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 314>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 314>::size() const;
template void soArrayVector<soStatusUniqProcess*, 314>::setSize(s32);
