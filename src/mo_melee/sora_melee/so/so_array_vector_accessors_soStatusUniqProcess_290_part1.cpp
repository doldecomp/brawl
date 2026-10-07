#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 290>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 290>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 290>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 290>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 290>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 290>::onFull();
template void soArrayVector<soStatusUniqProcess*, 290>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 290>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 290>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 290>::size() const;
template void soArrayVector<soStatusUniqProcess*, 290>::setSize(s32);
