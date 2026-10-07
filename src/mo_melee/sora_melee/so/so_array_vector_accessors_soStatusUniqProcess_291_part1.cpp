#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 291>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 291>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 291>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 291>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 291>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 291>::onFull();
template void soArrayVector<soStatusUniqProcess*, 291>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 291>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 291>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 291>::size() const;
template void soArrayVector<soStatusUniqProcess*, 291>::setSize(s32);
