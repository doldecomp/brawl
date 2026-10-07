#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soLinkConnection.h>

template s32 soArrayVector<soLinkConnection, 5>::getTopIndex() const;
template void soArrayVector<soLinkConnection, 5>::setTopIndex(s32);
template s32 soArrayVector<soLinkConnection, 5>::getLastIndex() const;
template void soArrayVector<soLinkConnection, 5>::setLastIndex(s32);
template soLinkConnection& soArrayVector<soLinkConnection, 5>::getArrayValueConst(s32);
template void soArrayVector<soLinkConnection, 5>::onFull();
template void soArrayVector<soLinkConnection, 5>::offFull();
template bool soArrayVector<soLinkConnection, 5>::isFull() const;
template s32 soArrayVector<soLinkConnection, 5>::capacity() const;
template s32 soArrayVector<soLinkConnection, 5>::size() const;
template void soArrayVector<soLinkConnection, 5>::setSize(s32);
