#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soEventUnit;

template s32 soArrayVector<soInstanceUnit<soEventUnit*>, 255>::getTopIndex() const;
template void soArrayVector<soInstanceUnit<soEventUnit*>, 255>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnit<soEventUnit*>, 255>::getLastIndex() const;
template void soArrayVector<soInstanceUnit<soEventUnit*>, 255>::setLastIndex(s32);
template soInstanceUnit<soEventUnit*>& soArrayVector<soInstanceUnit<soEventUnit*>, 255>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnit<soEventUnit*>, 255>::onFull();
template void soArrayVector<soInstanceUnit<soEventUnit*>, 255>::offFull();
template bool soArrayVector<soInstanceUnit<soEventUnit*>, 255>::isFull() const;
template s32 soArrayVector<soInstanceUnit<soEventUnit*>, 255>::capacity() const;
template s32 soArrayVector<soInstanceUnit<soEventUnit*>, 255>::size() const;
template soInstanceUnit<soEventUnit*>& soArrayVector<soInstanceUnit<soEventUnit*>, 255>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnit<soEventUnit*>, 255>::setSize(s32);
