#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 284>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 284>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 284>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 284>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 284>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 284>::onFull();
template void soArrayVector<soStatusUniqProcess*, 284>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 284>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 284>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 284>::size() const;
template void soArrayVector<soStatusUniqProcess*, 284>::setSize(s32);
