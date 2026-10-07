#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soEventUnit;

template s32 soArrayVector<soInstanceUnit<soEventUnit*>, 19>::getTopIndex() const;
template void soArrayVector<soInstanceUnit<soEventUnit*>, 19>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnit<soEventUnit*>, 19>::getLastIndex() const;
template void soArrayVector<soInstanceUnit<soEventUnit*>, 19>::setLastIndex(s32);
template soInstanceUnit<soEventUnit*>& soArrayVector<soInstanceUnit<soEventUnit*>, 19>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnit<soEventUnit*>, 19>::onFull();
template void soArrayVector<soInstanceUnit<soEventUnit*>, 19>::offFull();
template bool soArrayVector<soInstanceUnit<soEventUnit*>, 19>::isFull() const;
template s32 soArrayVector<soInstanceUnit<soEventUnit*>, 19>::capacity() const;
template s32 soArrayVector<soInstanceUnit<soEventUnit*>, 19>::size() const;
template soInstanceUnit<soEventUnit*>& soArrayVector<soInstanceUnit<soEventUnit*>, 19>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnit<soEventUnit*>, 19>::setSize(s32);
