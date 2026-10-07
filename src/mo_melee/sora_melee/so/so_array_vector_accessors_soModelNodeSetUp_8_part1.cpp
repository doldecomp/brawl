#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_model_node_set_up.h>

template s32 soArrayVector<soModelNodeSetUp, 8>::getTopIndex() const;
template void soArrayVector<soModelNodeSetUp, 8>::setTopIndex(s32);
template s32 soArrayVector<soModelNodeSetUp, 8>::getLastIndex() const;
template void soArrayVector<soModelNodeSetUp, 8>::setLastIndex(s32);
template soModelNodeSetUp& soArrayVector<soModelNodeSetUp, 8>::getArrayValueConst(s32);
template void soArrayVector<soModelNodeSetUp, 8>::onFull();
template void soArrayVector<soModelNodeSetUp, 8>::offFull();
template bool soArrayVector<soModelNodeSetUp, 8>::isFull() const;
template s32 soArrayVector<soModelNodeSetUp, 8>::capacity() const;
template s32 soArrayVector<soModelNodeSetUp, 8>::size() const;
template void soArrayVector<soModelNodeSetUp, 8>::setSize(s32);
