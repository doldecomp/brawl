#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_model_node_set_up.h>

template s32 soArrayVector<soModelNodeSetUp, 5>::getTopIndex() const;
template void soArrayVector<soModelNodeSetUp, 5>::setTopIndex(s32);
template s32 soArrayVector<soModelNodeSetUp, 5>::getLastIndex() const;
template void soArrayVector<soModelNodeSetUp, 5>::setLastIndex(s32);
template soModelNodeSetUp& soArrayVector<soModelNodeSetUp, 5>::getArrayValueConst(s32);
template void soArrayVector<soModelNodeSetUp, 5>::onFull();
template void soArrayVector<soModelNodeSetUp, 5>::offFull();
template bool soArrayVector<soModelNodeSetUp, 5>::isFull() const;
template s32 soArrayVector<soModelNodeSetUp, 5>::capacity() const;
template s32 soArrayVector<soModelNodeSetUp, 5>::size() const;
template void soArrayVector<soModelNodeSetUp, 5>::setSize(s32);
