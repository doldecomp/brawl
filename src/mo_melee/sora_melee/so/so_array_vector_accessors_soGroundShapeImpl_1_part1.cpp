#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soGroundShapeImpl.h>

template s32 soArrayVector<soGroundShapeImpl, 1>::getTopIndex() const;
template void soArrayVector<soGroundShapeImpl, 1>::setTopIndex(s32);
template s32 soArrayVector<soGroundShapeImpl, 1>::getLastIndex() const;
template void soArrayVector<soGroundShapeImpl, 1>::setLastIndex(s32);
template soGroundShapeImpl& soArrayVector<soGroundShapeImpl, 1>::getArrayValueConst(s32);
template void soArrayVector<soGroundShapeImpl, 1>::onFull();
template void soArrayVector<soGroundShapeImpl, 1>::offFull();
template bool soArrayVector<soGroundShapeImpl, 1>::isFull() const;
template s32 soArrayVector<soGroundShapeImpl, 1>::capacity() const;
template s32 soArrayVector<soGroundShapeImpl, 1>::size() const;
template void soArrayVector<soGroundShapeImpl, 1>::setSize(s32);
