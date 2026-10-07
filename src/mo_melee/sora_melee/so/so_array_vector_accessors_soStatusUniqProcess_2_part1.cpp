#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 2>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 2>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 2>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 2>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 2>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 2>::onFull();
template void soArrayVector<soStatusUniqProcess*, 2>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 2>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 2>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 2>::size() const;
template void soArrayVector<soStatusUniqProcess*, 2>::setSize(s32);
