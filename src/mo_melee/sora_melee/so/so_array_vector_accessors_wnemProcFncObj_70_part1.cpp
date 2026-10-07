#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_wnemProcFncObj.h>

template s32 soArrayVector<wnemProcFncObj, 70>::getTopIndex() const;
template void soArrayVector<wnemProcFncObj, 70>::setTopIndex(s32);
template s32 soArrayVector<wnemProcFncObj, 70>::getLastIndex() const;
template void soArrayVector<wnemProcFncObj, 70>::setLastIndex(s32);
template wnemProcFncObj& soArrayVector<wnemProcFncObj, 70>::getArrayValueConst(s32);
template void soArrayVector<wnemProcFncObj, 70>::onFull();
template void soArrayVector<wnemProcFncObj, 70>::offFull();
template bool soArrayVector<wnemProcFncObj, 70>::isFull() const;
template s32 soArrayVector<wnemProcFncObj, 70>::capacity() const;
template s32 soArrayVector<wnemProcFncObj, 70>::size() const;
template void soArrayVector<wnemProcFncObj, 70>::setSize(s32);
