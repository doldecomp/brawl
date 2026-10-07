#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_acCmdInterpreterStackData.h>

template s32 soArrayVector<acCmdInterpreterStackData, 2>::getTopIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 2>::setTopIndex(s32);
template s32 soArrayVector<acCmdInterpreterStackData, 2>::getLastIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 2>::setLastIndex(s32);
template acCmdInterpreterStackData& soArrayVector<acCmdInterpreterStackData, 2>::getArrayValueConst(s32);
template void soArrayVector<acCmdInterpreterStackData, 2>::onFull();
template void soArrayVector<acCmdInterpreterStackData, 2>::offFull();
template bool soArrayVector<acCmdInterpreterStackData, 2>::isFull() const;
template s32 soArrayVector<acCmdInterpreterStackData, 2>::capacity() const;
template s32 soArrayVector<acCmdInterpreterStackData, 2>::size() const;
template void soArrayVector<acCmdInterpreterStackData, 2>::setSize(s32);
