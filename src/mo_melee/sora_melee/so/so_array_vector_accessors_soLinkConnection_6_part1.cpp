#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soLinkConnection.h>

template s32 soArrayVector<soLinkConnection, 6>::getTopIndex() const;
template void soArrayVector<soLinkConnection, 6>::setTopIndex(s32);
template s32 soArrayVector<soLinkConnection, 6>::getLastIndex() const;
template void soArrayVector<soLinkConnection, 6>::setLastIndex(s32);
template soLinkConnection& soArrayVector<soLinkConnection, 6>::getArrayValueConst(s32);
template void soArrayVector<soLinkConnection, 6>::onFull();
template void soArrayVector<soLinkConnection, 6>::offFull();
template bool soArrayVector<soLinkConnection, 6>::isFull() const;
template s32 soArrayVector<soLinkConnection, 6>::capacity() const;
template s32 soArrayVector<soLinkConnection, 6>::size() const;
template void soArrayVector<soLinkConnection, 6>::setSize(s32);
