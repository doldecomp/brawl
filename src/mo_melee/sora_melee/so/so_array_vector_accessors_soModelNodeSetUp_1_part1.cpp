#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_model_node_set_up.h>

template s32 soArrayVector<soModelNodeSetUp, 1>::getTopIndex() const;
template void soArrayVector<soModelNodeSetUp, 1>::setTopIndex(s32);
template s32 soArrayVector<soModelNodeSetUp, 1>::getLastIndex() const;
template void soArrayVector<soModelNodeSetUp, 1>::setLastIndex(s32);
template soModelNodeSetUp& soArrayVector<soModelNodeSetUp, 1>::getArrayValueConst(s32);
template void soArrayVector<soModelNodeSetUp, 1>::onFull();
template void soArrayVector<soModelNodeSetUp, 1>::offFull();
template bool soArrayVector<soModelNodeSetUp, 1>::isFull() const;
template s32 soArrayVector<soModelNodeSetUp, 1>::capacity() const;
template s32 soArrayVector<soModelNodeSetUp, 1>::size() const;
template void soArrayVector<soModelNodeSetUp, 1>::setSize(s32);
