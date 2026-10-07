#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 301>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 301>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 301>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 301>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 301>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 301>::onFull();
template void soArrayVector<soStatusUniqProcess*, 301>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 301>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 301>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 301>::size() const;
template void soArrayVector<soStatusUniqProcess*, 301>::setSize(s32);
