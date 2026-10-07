#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 280>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 280>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 280>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 280>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 280>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 280>::onFull();
template void soArrayVector<soStatusUniqProcess*, 280>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 280>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 280>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 280>::size() const;
template void soArrayVector<soStatusUniqProcess*, 280>::setSize(s32);
