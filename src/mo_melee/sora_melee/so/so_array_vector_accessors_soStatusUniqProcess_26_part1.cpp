#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 26>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 26>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 26>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 26>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 26>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 26>::onFull();
template void soArrayVector<soStatusUniqProcess*, 26>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 26>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 26>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 26>::size() const;
template void soArrayVector<soStatusUniqProcess*, 26>::setSize(s32);
