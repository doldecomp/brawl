#pragma force_active on
#include <so/so_array.h>
#include <so/model/so_model_virtual_node.h>

template s32 soArrayVector<soModelVirtualNode, 3>::getTopIndex() const;
template void soArrayVector<soModelVirtualNode, 3>::setTopIndex(s32);
template s32 soArrayVector<soModelVirtualNode, 3>::getLastIndex() const;
template void soArrayVector<soModelVirtualNode, 3>::setLastIndex(s32);
template soModelVirtualNode& soArrayVector<soModelVirtualNode, 3>::getArrayValueConst(s32);
template void soArrayVector<soModelVirtualNode, 3>::onFull();
template void soArrayVector<soModelVirtualNode, 3>::offFull();
template bool soArrayVector<soModelVirtualNode, 3>::isFull() const;
template s32 soArrayVector<soModelVirtualNode, 3>::capacity() const;
template s32 soArrayVector<soModelVirtualNode, 3>::size() const;
template void soArrayVector<soModelVirtualNode, 3>::setSize(s32);
