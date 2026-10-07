#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 283>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 283>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 283>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 283>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 283>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 283>::onFull();
template void soArrayVector<soStatusUniqProcess*, 283>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 283>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 283>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 283>::size() const;
template void soArrayVector<soStatusUniqProcess*, 283>::setSize(s32);
