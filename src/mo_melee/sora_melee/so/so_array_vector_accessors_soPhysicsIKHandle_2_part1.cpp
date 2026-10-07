#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soPhysicsIKHandle.h>

template s32 soArrayVector<soPhysicsIKHandle, 2>::getTopIndex() const;
template void soArrayVector<soPhysicsIKHandle, 2>::setTopIndex(s32);
template s32 soArrayVector<soPhysicsIKHandle, 2>::getLastIndex() const;
template void soArrayVector<soPhysicsIKHandle, 2>::setLastIndex(s32);
template soPhysicsIKHandle& soArrayVector<soPhysicsIKHandle, 2>::getArrayValueConst(s32);
template void soArrayVector<soPhysicsIKHandle, 2>::onFull();
template void soArrayVector<soPhysicsIKHandle, 2>::offFull();
template bool soArrayVector<soPhysicsIKHandle, 2>::isFull() const;
template s32 soArrayVector<soPhysicsIKHandle, 2>::capacity() const;
template s32 soArrayVector<soPhysicsIKHandle, 2>::size() const;
template void soArrayVector<soPhysicsIKHandle, 2>::setSize(s32);
