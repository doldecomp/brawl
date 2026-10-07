#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 287>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 287>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 287>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 287>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 287>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 287>::onFull();
template void soArrayVector<soStatusUniqProcess*, 287>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 287>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 287>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 287>::size() const;
template void soArrayVector<soStatusUniqProcess*, 287>::setSize(s32);
