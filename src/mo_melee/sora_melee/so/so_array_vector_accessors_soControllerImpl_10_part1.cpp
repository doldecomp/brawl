#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_controller_impl.h>

template s32 soArrayVector<soControllerImpl, 10>::getTopIndex() const;
template void soArrayVector<soControllerImpl, 10>::setTopIndex(s32);
template s32 soArrayVector<soControllerImpl, 10>::getLastIndex() const;
template void soArrayVector<soControllerImpl, 10>::setLastIndex(s32);
template soControllerImpl& soArrayVector<soControllerImpl, 10>::getArrayValueConst(s32);
template void soArrayVector<soControllerImpl, 10>::onFull();
template void soArrayVector<soControllerImpl, 10>::offFull();
template bool soArrayVector<soControllerImpl, 10>::isFull() const;
template s32 soArrayVector<soControllerImpl, 10>::capacity() const;
template s32 soArrayVector<soControllerImpl, 10>::size() const;
template void soArrayVector<soControllerImpl, 10>::setSize(s32);
