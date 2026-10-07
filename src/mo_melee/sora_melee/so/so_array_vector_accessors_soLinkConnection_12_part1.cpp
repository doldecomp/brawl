#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soLinkConnection.h>

template s32 soArrayVector<soLinkConnection, 12>::getTopIndex() const;
template void soArrayVector<soLinkConnection, 12>::setTopIndex(s32);
template s32 soArrayVector<soLinkConnection, 12>::getLastIndex() const;
template void soArrayVector<soLinkConnection, 12>::setLastIndex(s32);
template soLinkConnection& soArrayVector<soLinkConnection, 12>::getArrayValueConst(s32);
template void soArrayVector<soLinkConnection, 12>::onFull();
template void soArrayVector<soLinkConnection, 12>::offFull();
template bool soArrayVector<soLinkConnection, 12>::isFull() const;
template s32 soArrayVector<soLinkConnection, 12>::capacity() const;
template s32 soArrayVector<soLinkConnection, 12>::size() const;
template void soArrayVector<soLinkConnection, 12>::setSize(s32);
