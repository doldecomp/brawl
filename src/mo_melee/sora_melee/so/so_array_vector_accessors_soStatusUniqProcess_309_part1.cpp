#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 309>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 309>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 309>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 309>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 309>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 309>::onFull();
template void soArrayVector<soStatusUniqProcess*, 309>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 309>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 309>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 309>::size() const;
template void soArrayVector<soStatusUniqProcess*, 309>::setSize(s32);
