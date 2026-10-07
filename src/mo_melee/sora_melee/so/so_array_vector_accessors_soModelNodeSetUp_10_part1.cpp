#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_model_node_set_up.h>

template s32 soArrayVector<soModelNodeSetUp, 10>::getTopIndex() const;
template void soArrayVector<soModelNodeSetUp, 10>::setTopIndex(s32);
template s32 soArrayVector<soModelNodeSetUp, 10>::getLastIndex() const;
template void soArrayVector<soModelNodeSetUp, 10>::setLastIndex(s32);
template soModelNodeSetUp& soArrayVector<soModelNodeSetUp, 10>::getArrayValueConst(s32);
template void soArrayVector<soModelNodeSetUp, 10>::onFull();
template void soArrayVector<soModelNodeSetUp, 10>::offFull();
template bool soArrayVector<soModelNodeSetUp, 10>::isFull() const;
template s32 soArrayVector<soModelNodeSetUp, 10>::capacity() const;
template s32 soArrayVector<soModelNodeSetUp, 10>::size() const;
template void soArrayVector<soModelNodeSetUp, 10>::setSize(s32);
