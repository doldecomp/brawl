#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 3>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 3>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 3>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 3>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 3>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 3>::onFull();
template void soArrayVector<soStatusUniqProcess*, 3>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 3>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 3>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 3>::size() const;
template void soArrayVector<soStatusUniqProcess*, 3>::setSize(s32);
