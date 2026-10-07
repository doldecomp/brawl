#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 289>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 289>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 289>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 289>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 289>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 289>::onFull();
template void soArrayVector<soStatusUniqProcess*, 289>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 289>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 289>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 289>::size() const;
template void soArrayVector<soStatusUniqProcess*, 289>::setSize(s32);
