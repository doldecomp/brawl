#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soEventManager;

template s32 soArrayVector<soInstanceUnit<soEventManager*>, 500>::getTopIndex() const;
template void soArrayVector<soInstanceUnit<soEventManager*>, 500>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnit<soEventManager*>, 500>::getLastIndex() const;
template void soArrayVector<soInstanceUnit<soEventManager*>, 500>::setLastIndex(s32);
template soInstanceUnit<soEventManager*>& soArrayVector<soInstanceUnit<soEventManager*>, 500>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnit<soEventManager*>, 500>::onFull();
template void soArrayVector<soInstanceUnit<soEventManager*>, 500>::offFull();
template bool soArrayVector<soInstanceUnit<soEventManager*>, 500>::isFull() const;
template s32 soArrayVector<soInstanceUnit<soEventManager*>, 500>::capacity() const;
template s32 soArrayVector<soInstanceUnit<soEventManager*>, 500>::size() const;
template soInstanceUnit<soEventManager*>& soArrayVector<soInstanceUnit<soEventManager*>, 500>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnit<soEventManager*>, 500>::setSize(s32);
