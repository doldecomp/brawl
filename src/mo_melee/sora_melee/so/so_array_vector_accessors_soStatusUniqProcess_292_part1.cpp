#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 292>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 292>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 292>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 292>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 292>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 292>::onFull();
template void soArrayVector<soStatusUniqProcess*, 292>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 292>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 292>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 292>::size() const;
template void soArrayVector<soStatusUniqProcess*, 292>::setSize(s32);
