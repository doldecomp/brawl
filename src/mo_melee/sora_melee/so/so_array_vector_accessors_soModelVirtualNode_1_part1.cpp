#pragma force_active on
#include <so/so_array.h>
#include <so/model/so_model_virtual_node.h>

template s32 soArrayVector<soModelVirtualNode, 1>::getTopIndex() const;
template void soArrayVector<soModelVirtualNode, 1>::setTopIndex(s32);
template s32 soArrayVector<soModelVirtualNode, 1>::getLastIndex() const;
template void soArrayVector<soModelVirtualNode, 1>::setLastIndex(s32);
template soModelVirtualNode& soArrayVector<soModelVirtualNode, 1>::getArrayValueConst(s32);
template void soArrayVector<soModelVirtualNode, 1>::onFull();
template void soArrayVector<soModelVirtualNode, 1>::offFull();
template bool soArrayVector<soModelVirtualNode, 1>::isFull() const;
template s32 soArrayVector<soModelVirtualNode, 1>::capacity() const;
template s32 soArrayVector<soModelVirtualNode, 1>::size() const;
template void soArrayVector<soModelVirtualNode, 1>::setSize(s32);
