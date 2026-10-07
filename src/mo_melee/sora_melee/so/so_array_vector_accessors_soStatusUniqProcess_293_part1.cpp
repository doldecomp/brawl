#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 293>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 293>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 293>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 293>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 293>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 293>::onFull();
template void soArrayVector<soStatusUniqProcess*, 293>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 293>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 293>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 293>::size() const;
template void soArrayVector<soStatusUniqProcess*, 293>::setSize(s32);
