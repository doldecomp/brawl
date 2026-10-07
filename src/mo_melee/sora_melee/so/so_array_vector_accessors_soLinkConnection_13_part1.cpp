#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soLinkConnection.h>

template s32 soArrayVector<soLinkConnection, 13>::getTopIndex() const;
template void soArrayVector<soLinkConnection, 13>::setTopIndex(s32);
template s32 soArrayVector<soLinkConnection, 13>::getLastIndex() const;
template void soArrayVector<soLinkConnection, 13>::setLastIndex(s32);
template soLinkConnection& soArrayVector<soLinkConnection, 13>::getArrayValueConst(s32);
template void soArrayVector<soLinkConnection, 13>::onFull();
template void soArrayVector<soLinkConnection, 13>::offFull();
template bool soArrayVector<soLinkConnection, 13>::isFull() const;
template s32 soArrayVector<soLinkConnection, 13>::capacity() const;
template s32 soArrayVector<soLinkConnection, 13>::size() const;
template void soArrayVector<soLinkConnection, 13>::setSize(s32);
