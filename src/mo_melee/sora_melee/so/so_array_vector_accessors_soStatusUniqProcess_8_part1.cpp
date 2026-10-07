#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 8>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 8>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 8>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 8>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 8>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 8>::onFull();
template void soArrayVector<soStatusUniqProcess*, 8>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 8>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 8>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 8>::size() const;
template void soArrayVector<soStatusUniqProcess*, 8>::setSize(s32);
