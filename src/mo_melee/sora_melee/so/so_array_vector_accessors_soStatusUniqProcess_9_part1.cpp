#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 9>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 9>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 9>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 9>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 9>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 9>::onFull();
template void soArrayVector<soStatusUniqProcess*, 9>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 9>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 9>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 9>::size() const;
template void soArrayVector<soStatusUniqProcess*, 9>::setSize(s32);
