#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 6>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 6>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 6>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 6>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 6>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 6>::onFull();
template void soArrayVector<soStatusUniqProcess*, 6>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 6>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 6>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 6>::size() const;
template void soArrayVector<soStatusUniqProcess*, 6>::setSize(s32);
