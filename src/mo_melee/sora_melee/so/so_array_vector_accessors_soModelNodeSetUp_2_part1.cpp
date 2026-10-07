#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_model_node_set_up.h>

template s32 soArrayVector<soModelNodeSetUp, 2>::getTopIndex() const;
template void soArrayVector<soModelNodeSetUp, 2>::setTopIndex(s32);
template s32 soArrayVector<soModelNodeSetUp, 2>::getLastIndex() const;
template void soArrayVector<soModelNodeSetUp, 2>::setLastIndex(s32);
template soModelNodeSetUp& soArrayVector<soModelNodeSetUp, 2>::getArrayValueConst(s32);
template void soArrayVector<soModelNodeSetUp, 2>::onFull();
template void soArrayVector<soModelNodeSetUp, 2>::offFull();
template bool soArrayVector<soModelNodeSetUp, 2>::isFull() const;
template s32 soArrayVector<soModelNodeSetUp, 2>::capacity() const;
template s32 soArrayVector<soModelNodeSetUp, 2>::size() const;
template void soArrayVector<soModelNodeSetUp, 2>::setSize(s32);
