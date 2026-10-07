#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_controller_impl.h>

template s32 soArrayVector<soControllerImpl, 1>::getTopIndex() const;
template void soArrayVector<soControllerImpl, 1>::setTopIndex(s32);
template s32 soArrayVector<soControllerImpl, 1>::getLastIndex() const;
template void soArrayVector<soControllerImpl, 1>::setLastIndex(s32);
template soControllerImpl& soArrayVector<soControllerImpl, 1>::getArrayValueConst(s32);
template void soArrayVector<soControllerImpl, 1>::onFull();
template void soArrayVector<soControllerImpl, 1>::offFull();
template bool soArrayVector<soControllerImpl, 1>::isFull() const;
template s32 soArrayVector<soControllerImpl, 1>::capacity() const;
template s32 soArrayVector<soControllerImpl, 1>::size() const;
template void soArrayVector<soControllerImpl, 1>::setSize(s32);
