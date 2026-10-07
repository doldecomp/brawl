#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_acCmdInterpreterStackData.h>

template s32 soArrayVector<acCmdInterpreterStackData, 3>::getTopIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 3>::setTopIndex(s32);
template s32 soArrayVector<acCmdInterpreterStackData, 3>::getLastIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 3>::setLastIndex(s32);
template acCmdInterpreterStackData& soArrayVector<acCmdInterpreterStackData, 3>::getArrayValueConst(s32);
template void soArrayVector<acCmdInterpreterStackData, 3>::onFull();
template void soArrayVector<acCmdInterpreterStackData, 3>::offFull();
template bool soArrayVector<acCmdInterpreterStackData, 3>::isFull() const;
template s32 soArrayVector<acCmdInterpreterStackData, 3>::capacity() const;
template s32 soArrayVector<acCmdInterpreterStackData, 3>::size() const;
template void soArrayVector<acCmdInterpreterStackData, 3>::setSize(s32);
