#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 1>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 1>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 1>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 1>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 1>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 1>::onFull();
template void soArrayVector<soStatusUniqProcess*, 1>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 1>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 1>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 1>::size() const;
template void soArrayVector<soStatusUniqProcess*, 1>::setSize(s32);
