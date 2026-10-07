#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_acCmdInterpreterStackData.h>

template s32 soArrayVector<acCmdInterpreterStackData, 1>::getTopIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 1>::setTopIndex(s32);
template s32 soArrayVector<acCmdInterpreterStackData, 1>::getLastIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 1>::setLastIndex(s32);
template acCmdInterpreterStackData& soArrayVector<acCmdInterpreterStackData, 1>::getArrayValueConst(s32);
template void soArrayVector<acCmdInterpreterStackData, 1>::onFull();
template void soArrayVector<acCmdInterpreterStackData, 1>::offFull();
template bool soArrayVector<acCmdInterpreterStackData, 1>::isFull() const;
template s32 soArrayVector<acCmdInterpreterStackData, 1>::capacity() const;
template s32 soArrayVector<acCmdInterpreterStackData, 1>::size() const;
template void soArrayVector<acCmdInterpreterStackData, 1>::setSize(s32);
