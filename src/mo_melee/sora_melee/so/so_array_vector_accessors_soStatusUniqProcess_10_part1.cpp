#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 10>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 10>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 10>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 10>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 10>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 10>::onFull();
template void soArrayVector<soStatusUniqProcess*, 10>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 10>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 10>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 10>::size() const;
template void soArrayVector<soStatusUniqProcess*, 10>::setSize(s32);
