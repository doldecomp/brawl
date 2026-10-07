#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 299>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 299>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 299>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 299>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 299>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 299>::onFull();
template void soArrayVector<soStatusUniqProcess*, 299>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 299>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 299>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 299>::size() const;
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 299>::atFastAbstractSub(s32) const;
template void soArrayVector<soStatusUniqProcess*, 299>::setSize(s32);
