#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 19>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 19>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 19>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 19>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 19>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 19>::onFull();
template void soArrayVector<soStatusUniqProcess*, 19>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 19>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 19>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 19>::size() const;
template void soArrayVector<soStatusUniqProcess*, 19>::setSize(s32);
