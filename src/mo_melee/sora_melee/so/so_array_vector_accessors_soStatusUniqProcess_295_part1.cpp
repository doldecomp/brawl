#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 295>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 295>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 295>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 295>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 295>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 295>::onFull();
template void soArrayVector<soStatusUniqProcess*, 295>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 295>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 295>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 295>::size() const;
template void soArrayVector<soStatusUniqProcess*, 295>::setSize(s32);
