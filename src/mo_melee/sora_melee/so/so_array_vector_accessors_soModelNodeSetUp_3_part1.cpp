#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_model_node_set_up.h>

template s32 soArrayVector<soModelNodeSetUp, 3>::getTopIndex() const;
template void soArrayVector<soModelNodeSetUp, 3>::setTopIndex(s32);
template s32 soArrayVector<soModelNodeSetUp, 3>::getLastIndex() const;
template void soArrayVector<soModelNodeSetUp, 3>::setLastIndex(s32);
template soModelNodeSetUp& soArrayVector<soModelNodeSetUp, 3>::getArrayValueConst(s32);
template void soArrayVector<soModelNodeSetUp, 3>::onFull();
template void soArrayVector<soModelNodeSetUp, 3>::offFull();
template bool soArrayVector<soModelNodeSetUp, 3>::isFull() const;
template s32 soArrayVector<soModelNodeSetUp, 3>::capacity() const;
template s32 soArrayVector<soModelNodeSetUp, 3>::size() const;
template void soArrayVector<soModelNodeSetUp, 3>::setSize(s32);
