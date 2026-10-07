#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soAreaContactLog.h>

template s32 soArrayVector<soAreaContactLog, 8>::getTopIndex() const;
template void soArrayVector<soAreaContactLog, 8>::setTopIndex(s32);
template s32 soArrayVector<soAreaContactLog, 8>::getLastIndex() const;
template void soArrayVector<soAreaContactLog, 8>::setLastIndex(s32);
template soAreaContactLog& soArrayVector<soAreaContactLog, 8>::getArrayValueConst(s32);
template void soArrayVector<soAreaContactLog, 8>::onFull();
template void soArrayVector<soAreaContactLog, 8>::offFull();
template bool soArrayVector<soAreaContactLog, 8>::isFull() const;
template s32 soArrayVector<soAreaContactLog, 8>::capacity() const;
template s32 soArrayVector<soAreaContactLog, 8>::size() const;
template soAreaContactLog& soArrayVector<soAreaContactLog, 8>::atFastAbstractSub(s32) const;
template void soArrayVector<soAreaContactLog, 8>::setSize(s32);
