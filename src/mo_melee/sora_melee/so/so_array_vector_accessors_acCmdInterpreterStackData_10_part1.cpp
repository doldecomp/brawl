#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_acCmdInterpreterStackData.h>

template s32 soArrayVector<acCmdInterpreterStackData, 10>::getTopIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 10>::setTopIndex(s32);
template s32 soArrayVector<acCmdInterpreterStackData, 10>::getLastIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 10>::setLastIndex(s32);
template acCmdInterpreterStackData& soArrayVector<acCmdInterpreterStackData, 10>::getArrayValueConst(s32);
template void soArrayVector<acCmdInterpreterStackData, 10>::onFull();
template void soArrayVector<acCmdInterpreterStackData, 10>::offFull();
template bool soArrayVector<acCmdInterpreterStackData, 10>::isFull() const;
template s32 soArrayVector<acCmdInterpreterStackData, 10>::capacity() const;
template s32 soArrayVector<acCmdInterpreterStackData, 10>::size() const;
template void soArrayVector<acCmdInterpreterStackData, 10>::setSize(s32);
