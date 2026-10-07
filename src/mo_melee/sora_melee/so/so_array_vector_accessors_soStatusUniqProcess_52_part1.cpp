#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 52>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 52>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 52>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 52>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 52>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 52>::onFull();
template void soArrayVector<soStatusUniqProcess*, 52>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 52>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 52>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 52>::size() const;
template void soArrayVector<soStatusUniqProcess*, 52>::setSize(s32);
