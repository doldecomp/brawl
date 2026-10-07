#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_acCmdInterpreterStackData.h>

template s32 soArrayVector<acCmdInterpreterStackData, 12>::getTopIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 12>::setTopIndex(s32);
template s32 soArrayVector<acCmdInterpreterStackData, 12>::getLastIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 12>::setLastIndex(s32);
template acCmdInterpreterStackData& soArrayVector<acCmdInterpreterStackData, 12>::getArrayValueConst(s32);
template void soArrayVector<acCmdInterpreterStackData, 12>::onFull();
template void soArrayVector<acCmdInterpreterStackData, 12>::offFull();
template bool soArrayVector<acCmdInterpreterStackData, 12>::isFull() const;
template s32 soArrayVector<acCmdInterpreterStackData, 12>::capacity() const;
template s32 soArrayVector<acCmdInterpreterStackData, 12>::size() const;
template void soArrayVector<acCmdInterpreterStackData, 12>::setSize(s32);
