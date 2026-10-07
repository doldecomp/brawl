#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_model_node_set_up.h>

template s32 soArrayVector<soModelNodeSetUp, 4>::getTopIndex() const;
template void soArrayVector<soModelNodeSetUp, 4>::setTopIndex(s32);
template s32 soArrayVector<soModelNodeSetUp, 4>::getLastIndex() const;
template void soArrayVector<soModelNodeSetUp, 4>::setLastIndex(s32);
template soModelNodeSetUp& soArrayVector<soModelNodeSetUp, 4>::getArrayValueConst(s32);
template void soArrayVector<soModelNodeSetUp, 4>::onFull();
template void soArrayVector<soModelNodeSetUp, 4>::offFull();
template bool soArrayVector<soModelNodeSetUp, 4>::isFull() const;
template s32 soArrayVector<soModelNodeSetUp, 4>::capacity() const;
template s32 soArrayVector<soModelNodeSetUp, 4>::size() const;
template soModelNodeSetUp& soArrayVector<soModelNodeSetUp, 4>::atFastAbstractSub(s32) const;
template void soArrayVector<soModelNodeSetUp, 4>::setSize(s32);
