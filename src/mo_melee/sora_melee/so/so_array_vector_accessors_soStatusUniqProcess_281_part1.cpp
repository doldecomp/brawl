#pragma force_active on
#include <so/so_array.h>
class soStatusUniqProcess;

template s32 soArrayVector<soStatusUniqProcess*, 281>::getTopIndex() const;
template void soArrayVector<soStatusUniqProcess*, 281>::setTopIndex(s32);
template s32 soArrayVector<soStatusUniqProcess*, 281>::getLastIndex() const;
template void soArrayVector<soStatusUniqProcess*, 281>::setLastIndex(s32);
template soStatusUniqProcess*& soArrayVector<soStatusUniqProcess*, 281>::getArrayValueConst(s32);
template void soArrayVector<soStatusUniqProcess*, 281>::onFull();
template void soArrayVector<soStatusUniqProcess*, 281>::offFull();
template bool soArrayVector<soStatusUniqProcess*, 281>::isFull() const;
template s32 soArrayVector<soStatusUniqProcess*, 281>::capacity() const;
template s32 soArrayVector<soStatusUniqProcess*, 281>::size() const;
template void soArrayVector<soStatusUniqProcess*, 281>::setSize(s32);
