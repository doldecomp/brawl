#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soAreaContactLog.h>

template s32 soArrayVector<soAreaContactLog, 16>::getTopIndex() const;
template void soArrayVector<soAreaContactLog, 16>::setTopIndex(s32);
template s32 soArrayVector<soAreaContactLog, 16>::getLastIndex() const;
template void soArrayVector<soAreaContactLog, 16>::setLastIndex(s32);
template soAreaContactLog& soArrayVector<soAreaContactLog, 16>::getArrayValueConst(s32);
template void soArrayVector<soAreaContactLog, 16>::onFull();
template void soArrayVector<soAreaContactLog, 16>::offFull();
template bool soArrayVector<soAreaContactLog, 16>::isFull() const;
template s32 soArrayVector<soAreaContactLog, 16>::capacity() const;
template s32 soArrayVector<soAreaContactLog, 16>::size() const;
template void soArrayVector<soAreaContactLog, 16>::setSize(s32);
