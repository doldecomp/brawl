#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soLinkConnection.h>

template s32 soArrayVector<soLinkConnection, 8>::getTopIndex() const;
template void soArrayVector<soLinkConnection, 8>::setTopIndex(s32);
template s32 soArrayVector<soLinkConnection, 8>::getLastIndex() const;
template void soArrayVector<soLinkConnection, 8>::setLastIndex(s32);
template soLinkConnection& soArrayVector<soLinkConnection, 8>::getArrayValueConst(s32);
template void soArrayVector<soLinkConnection, 8>::onFull();
template void soArrayVector<soLinkConnection, 8>::offFull();
template bool soArrayVector<soLinkConnection, 8>::isFull() const;
template s32 soArrayVector<soLinkConnection, 8>::capacity() const;
template s32 soArrayVector<soLinkConnection, 8>::size() const;
template void soArrayVector<soLinkConnection, 8>::setSize(s32);
