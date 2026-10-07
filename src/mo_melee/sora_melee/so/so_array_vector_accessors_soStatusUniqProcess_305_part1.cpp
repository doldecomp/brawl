#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 305>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 305>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 305>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 305>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 305>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 305>::onFull();
template void soArrayVector<soStatusUniqProcess*, 305>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 305>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 305>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 305>::size() const;
template void soArrayVector<soStatusUniqProcess*, 305>::setSize(s32);
