#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 4>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 4>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 4>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 4>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 4>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 4>::onFull();
template void soArrayVector<soStatusUniqProcess*, 4>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 4>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 4>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 4>::size() const;
template void soArrayVector<soStatusUniqProcess*, 4>::setSize(s32);
