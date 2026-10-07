#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soEventUnit;

template s32 soArrayVector<soInstanceUnit<soEventUnit*>, 4>::getTopIndex() const;
template void soArrayVector<soInstanceUnit<soEventUnit*>, 4>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnit<soEventUnit*>, 4>::getLastIndex() const;
template void soArrayVector<soInstanceUnit<soEventUnit*>, 4>::setLastIndex(s32);
template soInstanceUnit<soEventUnit*>& soArrayVector<soInstanceUnit<soEventUnit*>, 4>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnit<soEventUnit*>, 4>::onFull();
template void soArrayVector<soInstanceUnit<soEventUnit*>, 4>::offFull();
template bool soArrayVector<soInstanceUnit<soEventUnit*>, 4>::isFull() const;
template s32 soArrayVector<soInstanceUnit<soEventUnit*>, 4>::capacity() const;
template s32 soArrayVector<soInstanceUnit<soEventUnit*>, 4>::size() const;
template soInstanceUnit<soEventUnit*>& soArrayVector<soInstanceUnit<soEventUnit*>, 4>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnit<soEventUnit*>, 4>::setSize(s32);
