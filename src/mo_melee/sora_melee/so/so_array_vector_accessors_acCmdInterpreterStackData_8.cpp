#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_acCmdInterpreterStackData.h>

template s32 soArrayVector<acCmdInterpreterStackData, 8>::getTopIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 8>::setTopIndex(s32);
template s32 soArrayVector<acCmdInterpreterStackData, 8>::getLastIndex() const;
template void soArrayVector<acCmdInterpreterStackData, 8>::setLastIndex(s32);
template acCmdInterpreterStackData& soArrayVector<acCmdInterpreterStackData, 8>::getArrayValueConst(s32);
template void soArrayVector<acCmdInterpreterStackData, 8>::onFull();
template void soArrayVector<acCmdInterpreterStackData, 8>::offFull();
template bool soArrayVector<acCmdInterpreterStackData, 8>::isFull() const;
template s32 soArrayVector<acCmdInterpreterStackData, 8>::capacity() const;
template s32 soArrayVector<acCmdInterpreterStackData, 8>::size() const;
template acCmdInterpreterStackData& soArrayVector<acCmdInterpreterStackData, 8>::atFastAbstractSub(s32) const;
template void soArrayVector<acCmdInterpreterStackData, 8>::setSize(s32);
