#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_model_node_set_up.h>

template s32 soArrayVector<soModelNodeSetUp, 11>::getTopIndex() const;
template void soArrayVector<soModelNodeSetUp, 11>::setTopIndex(s32);
template s32 soArrayVector<soModelNodeSetUp, 11>::getLastIndex() const;
template void soArrayVector<soModelNodeSetUp, 11>::setLastIndex(s32);
template soModelNodeSetUp& soArrayVector<soModelNodeSetUp, 11>::getArrayValueConst(s32);
template void soArrayVector<soModelNodeSetUp, 11>::onFull();
template void soArrayVector<soModelNodeSetUp, 11>::offFull();
template bool soArrayVector<soModelNodeSetUp, 11>::isFull() const;
template s32 soArrayVector<soModelNodeSetUp, 11>::capacity() const;
template s32 soArrayVector<soModelNodeSetUp, 11>::size() const;
template void soArrayVector<soModelNodeSetUp, 11>::setSize(s32);
