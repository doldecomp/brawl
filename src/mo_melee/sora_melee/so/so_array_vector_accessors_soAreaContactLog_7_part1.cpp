#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soAreaContactLog.h>

template s32 soArrayVector<soAreaContactLog, 7>::getTopIndex() const;
template void soArrayVector<soAreaContactLog, 7>::setTopIndex(s32);
template s32 soArrayVector<soAreaContactLog, 7>::getLastIndex() const;
template void soArrayVector<soAreaContactLog, 7>::setLastIndex(s32);
template soAreaContactLog& soArrayVector<soAreaContactLog, 7>::getArrayValueConst(s32);
template void soArrayVector<soAreaContactLog, 7>::onFull();
template void soArrayVector<soAreaContactLog, 7>::offFull();
template bool soArrayVector<soAreaContactLog, 7>::isFull() const;
template s32 soArrayVector<soAreaContactLog, 7>::capacity() const;
template s32 soArrayVector<soAreaContactLog, 7>::size() const;
template void soArrayVector<soAreaContactLog, 7>::setSize(s32);
