#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soLinkConnection.h>

template s32 soArrayVector<soLinkConnection, 9>::getTopIndex() const;
template void soArrayVector<soLinkConnection, 9>::setTopIndex(s32);
template s32 soArrayVector<soLinkConnection, 9>::getLastIndex() const;
template void soArrayVector<soLinkConnection, 9>::setLastIndex(s32);
template soLinkConnection& soArrayVector<soLinkConnection, 9>::getArrayValueConst(s32);
template void soArrayVector<soLinkConnection, 9>::onFull();
template void soArrayVector<soLinkConnection, 9>::offFull();
template bool soArrayVector<soLinkConnection, 9>::isFull() const;
template s32 soArrayVector<soLinkConnection, 9>::capacity() const;
template s32 soArrayVector<soLinkConnection, 9>::size() const;
template void soArrayVector<soLinkConnection, 9>::setSize(s32);
