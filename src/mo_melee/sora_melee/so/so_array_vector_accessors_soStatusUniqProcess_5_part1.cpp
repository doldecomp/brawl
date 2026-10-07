#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 5>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 5>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 5>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 5>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 5>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 5>::onFull();
template void soArrayVector<soStatusUniqProcess*, 5>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 5>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 5>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 5>::size() const;
template void soArrayVector<soStatusUniqProcess*, 5>::setSize(s32);
