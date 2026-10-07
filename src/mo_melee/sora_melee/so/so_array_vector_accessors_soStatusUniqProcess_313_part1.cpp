#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 313>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 313>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 313>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 313>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 313>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 313>::onFull();
template void soArrayVector<soStatusUniqProcess*, 313>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 313>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 313>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 313>::size() const;
template void soArrayVector<soStatusUniqProcess*, 313>::setSize(s32);
