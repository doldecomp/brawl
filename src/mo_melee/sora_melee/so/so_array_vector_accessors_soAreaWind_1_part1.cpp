#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soAreaWind.h>

template s32 soArrayVector<soAreaWind, 1>::getTopIndex() const;
template void soArrayVector<soAreaWind, 1>::setTopIndex(s32);
template s32 soArrayVector<soAreaWind, 1>::getLastIndex() const;
template void soArrayVector<soAreaWind, 1>::setLastIndex(s32);
template soAreaWind& soArrayVector<soAreaWind, 1>::getArrayValueConst(s32);
template void soArrayVector<soAreaWind, 1>::onFull();
template void soArrayVector<soAreaWind, 1>::offFull();
template bool soArrayVector<soAreaWind, 1>::isFull() const;
template s32 soArrayVector<soAreaWind, 1>::capacity() const;
template s32 soArrayVector<soAreaWind, 1>::size() const;
template void soArrayVector<soAreaWind, 1>::setSize(s32);
