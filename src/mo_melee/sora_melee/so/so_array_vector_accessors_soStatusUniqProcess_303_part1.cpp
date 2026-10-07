#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 303>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 303>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 303>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 303>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 303>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 303>::onFull();
template void soArrayVector<soStatusUniqProcess*, 303>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 303>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 303>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 303>::size() const;
template void soArrayVector<soStatusUniqProcess*, 303>::setSize(s32);
