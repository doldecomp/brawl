#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soAnimCmdAddressPack.h>

template s32 soArrayVector<soAnimCmdAddressPack, 20>::getTopIndex() const;
template void soArrayVector<soAnimCmdAddressPack, 20>::setTopIndex(s32);
template s32 soArrayVector<soAnimCmdAddressPack, 20>::getLastIndex() const;
template void soArrayVector<soAnimCmdAddressPack, 20>::setLastIndex(s32);
template soAnimCmdAddressPack& soArrayVector<soAnimCmdAddressPack, 20>::getArrayValueConst(s32);
template void soArrayVector<soAnimCmdAddressPack, 20>::onFull();
template void soArrayVector<soAnimCmdAddressPack, 20>::offFull();
template bool soArrayVector<soAnimCmdAddressPack, 20>::isFull() const;
template s32 soArrayVector<soAnimCmdAddressPack, 20>::capacity() const;
template s32 soArrayVector<soAnimCmdAddressPack, 20>::size() const;
template soAnimCmdAddressPack& soArrayVector<soAnimCmdAddressPack, 20>::atFastAbstractSub(s32) const;
template void soArrayVector<soAnimCmdAddressPack, 20>::setSize(s32);
