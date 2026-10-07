#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soLinkConnection.h>

template s32 soArrayVector<soLinkConnection, 7>::getTopIndex() const;
template void soArrayVector<soLinkConnection, 7>::setTopIndex(s32);
template s32 soArrayVector<soLinkConnection, 7>::getLastIndex() const;
template void soArrayVector<soLinkConnection, 7>::setLastIndex(s32);
template soLinkConnection& soArrayVector<soLinkConnection, 7>::getArrayValueConst(s32);
template void soArrayVector<soLinkConnection, 7>::onFull();
template void soArrayVector<soLinkConnection, 7>::offFull();
template bool soArrayVector<soLinkConnection, 7>::isFull() const;
template s32 soArrayVector<soLinkConnection, 7>::capacity() const;
template s32 soArrayVector<soLinkConnection, 7>::size() const;
template void soArrayVector<soLinkConnection, 7>::setSize(s32);
