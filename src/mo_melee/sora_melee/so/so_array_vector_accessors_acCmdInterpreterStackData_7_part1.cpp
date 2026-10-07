#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_acCmdInterpreterStackData.h>

template s32 soArrayVector<acCmdInterpreterStackData, 7>::getTopIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 7>::setTopIndex(s32);
template s32 soArrayVector<acCmdInterpreterStackData, 7>::getLastIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 7>::setLastIndex(s32);
template acCmdInterpreterStackData& soArrayVector<acCmdInterpreterStackData, 7>::getArrayValueConst(s32);
template void soArrayVector<acCmdInterpreterStackData, 7>::onFull();
template void soArrayVector<acCmdInterpreterStackData, 7>::offFull();
template bool soArrayVector<acCmdInterpreterStackData, 7>::isFull() const;
template s32 soArrayVector<acCmdInterpreterStackData, 7>::capacity() const;
template s32 soArrayVector<acCmdInterpreterStackData, 7>::size() const;
template void soArrayVector<acCmdInterpreterStackData, 7>::setSize(s32);
