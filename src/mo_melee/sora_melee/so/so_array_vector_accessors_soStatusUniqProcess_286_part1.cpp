#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 286>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 286>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 286>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 286>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 286>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 286>::onFull();
template void soArrayVector<soStatusUniqProcess*, 286>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 286>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 286>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 286>::size() const;
template void soArrayVector<soStatusUniqProcess*, 286>::setSize(s32);
