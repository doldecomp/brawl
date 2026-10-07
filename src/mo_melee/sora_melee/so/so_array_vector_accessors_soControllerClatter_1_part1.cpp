#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soControllerClatter.h>

template s32 soArrayVector<soControllerClatter, 1>::getTopIndex() const;
template void soArrayVector<soControllerClatter, 1>::setTopIndex(s32);
template s32 soArrayVector<soControllerClatter, 1>::getLastIndex() const;
template void soArrayVector<soControllerClatter, 1>::setLastIndex(s32);
template soControllerClatter& soArrayVector<soControllerClatter, 1>::getArrayValueConst(s32);
template void soArrayVector<soControllerClatter, 1>::onFull();
template void soArrayVector<soControllerClatter, 1>::offFull();
template bool soArrayVector<soControllerClatter, 1>::isFull() const;
template s32 soArrayVector<soControllerClatter, 1>::capacity() const;
template s32 soArrayVector<soControllerClatter, 1>::size() const;
template void soArrayVector<soControllerClatter, 1>::setSize(s32);
