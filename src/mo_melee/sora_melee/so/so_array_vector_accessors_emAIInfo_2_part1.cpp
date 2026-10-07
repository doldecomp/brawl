#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_emAIInfo.h>

template s32 soArrayVector<emAIInfo, 2>::getTopIndex() const;
template void soArrayVector<emAIInfo, 2>::setTopIndex(s32);
template s32 soArrayVector<emAIInfo, 2>::getLastIndex() const;
template void soArrayVector<emAIInfo, 2>::setLastIndex(s32);
template emAIInfo& soArrayVector<emAIInfo, 2>::getArrayValueConst(s32);
template void soArrayVector<emAIInfo, 2>::onFull();
template void soArrayVector<emAIInfo, 2>::offFull();
template bool soArrayVector<emAIInfo, 2>::isFull() const;
template s32 soArrayVector<emAIInfo, 2>::capacity() const;
template s32 soArrayVector<emAIInfo, 2>::size() const;
template void soArrayVector<emAIInfo, 2>::setSize(s32);
