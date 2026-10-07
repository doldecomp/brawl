#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_model_node_set_up.h>

template s32 soArrayVector<soModelNodeSetUp, 7>::getTopIndex() const;
template void soArrayVector<soModelNodeSetUp, 7>::setTopIndex(s32);
template s32 soArrayVector<soModelNodeSetUp, 7>::getLastIndex() const;
template void soArrayVector<soModelNodeSetUp, 7>::setLastIndex(s32);
template soModelNodeSetUp& soArrayVector<soModelNodeSetUp, 7>::getArrayValueConst(s32);
template void soArrayVector<soModelNodeSetUp, 7>::onFull();
template void soArrayVector<soModelNodeSetUp, 7>::offFull();
template bool soArrayVector<soModelNodeSetUp, 7>::isFull() const;
template s32 soArrayVector<soModelNodeSetUp, 7>::capacity() const;
template s32 soArrayVector<soModelNodeSetUp, 7>::size() const;
template soModelNodeSetUp& soArrayVector<soModelNodeSetUp, 7>::atFastAbstractSub(s32) const;
template void soArrayVector<soModelNodeSetUp, 7>::setSize(s32);
