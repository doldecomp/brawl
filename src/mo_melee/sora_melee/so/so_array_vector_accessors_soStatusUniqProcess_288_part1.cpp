#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 288>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 288>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 288>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 288>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 288>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 288>::onFull();
template void soArrayVector<soStatusUniqProcess*, 288>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 288>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 288>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 288>::size() const;
template void soArrayVector<soStatusUniqProcess*, 288>::setSize(s32);
