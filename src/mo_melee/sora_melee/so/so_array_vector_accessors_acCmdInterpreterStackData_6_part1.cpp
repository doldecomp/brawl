#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_acCmdInterpreterStackData.h>

template s32 soArrayVector<acCmdInterpreterStackData, 6>::getTopIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 6>::setTopIndex(s32);
template s32 soArrayVector<acCmdInterpreterStackData, 6>::getLastIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 6>::setLastIndex(s32);
template acCmdInterpreterStackData& soArrayVector<acCmdInterpreterStackData, 6>::getArrayValueConst(s32);
template void soArrayVector<acCmdInterpreterStackData, 6>::onFull();
template void soArrayVector<acCmdInterpreterStackData, 6>::offFull();
template bool soArrayVector<acCmdInterpreterStackData, 6>::isFull() const;
template s32 soArrayVector<acCmdInterpreterStackData, 6>::capacity() const;
template s32 soArrayVector<acCmdInterpreterStackData, 6>::size() const;
template void soArrayVector<acCmdInterpreterStackData, 6>::setSize(s32);
