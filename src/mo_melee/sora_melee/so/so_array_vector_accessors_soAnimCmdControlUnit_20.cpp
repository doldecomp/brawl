#pragma force_active on
#include <so/so_array.h>
class soAnimCmdControlUnit;

template s32 soArrayVector<soAnimCmdControlUnit*, 20>::size() const;
template s32 soArrayVector<soAnimCmdControlUnit*, 20>::getTopIndex() const;
template void soArrayVector<soAnimCmdControlUnit*, 20>::setTopIndex(s32);
template s32 soArrayVector<soAnimCmdControlUnit*, 20>::getLastIndex() const;
template void soArrayVector<soAnimCmdControlUnit*, 20>::setLastIndex(s32);
template soAnimCmdControlUnit*& soArrayVector<soAnimCmdControlUnit*, 20>::getArrayValueConst(s32);
template void soArrayVector<soAnimCmdControlUnit*, 20>::onFull();
template void soArrayVector<soAnimCmdControlUnit*, 20>::offFull();
template bool soArrayVector<soAnimCmdControlUnit*, 20>::isFull() const;
template s32 soArrayVector<soAnimCmdControlUnit*, 20>::capacity() const;
template soAnimCmdControlUnit*& soArrayVector<soAnimCmdControlUnit*, 20>::atFastAbstractSub(s32) const;
template void soArrayVector<soAnimCmdControlUnit*, 20>::setSize(s32);
