#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 285>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 285>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 285>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 285>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 285>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 285>::onFull();
template void soArrayVector<soStatusUniqProcess*, 285>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 285>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 285>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 285>::size() const;
template void soArrayVector<soStatusUniqProcess*, 285>::setSize(s32);
