#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soAreaContactLog.h>

template s32 soArrayVector<soAreaContactLog, 44>::getTopIndex() const;
template void soArrayVector<soAreaContactLog, 44>::setTopIndex(s32);
template s32 soArrayVector<soAreaContactLog, 44>::getLastIndex() const;
template void soArrayVector<soAreaContactLog, 44>::setLastIndex(s32);
template soAreaContactLog& soArrayVector<soAreaContactLog, 44>::getArrayValueConst(s32);
template void soArrayVector<soAreaContactLog, 44>::onFull();
template void soArrayVector<soAreaContactLog, 44>::offFull();
template bool soArrayVector<soAreaContactLog, 44>::isFull() const;
template s32 soArrayVector<soAreaContactLog, 44>::capacity() const;
template s32 soArrayVector<soAreaContactLog, 44>::size() const;
template void soArrayVector<soAreaContactLog, 44>::setSize(s32);
