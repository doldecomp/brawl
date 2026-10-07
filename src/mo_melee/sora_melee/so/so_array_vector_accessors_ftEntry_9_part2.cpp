#pragma force_active on
#include <so/so_array.h>
class ftEntry;

template s32 soArrayVector<ftEntry*, 9>::getTopIndex() const;
template void soArrayVector<ftEntry*, 9>::setTopIndex(s32);
template s32 soArrayVector<ftEntry*, 9>::getLastIndex() const;
template void soArrayVector<ftEntry*, 9>::setLastIndex(s32);
template ftEntry*& soArrayVector<ftEntry*, 9>::getArrayValueConst(s32);
template void soArrayVector<ftEntry*, 9>::onFull();
template void soArrayVector<ftEntry*, 9>::offFull();
template bool soArrayVector<ftEntry*, 9>::isFull() const;
template s32 soArrayVector<ftEntry*, 9>::capacity() const;
template ftEntry*& soArrayVector<ftEntry*, 9>::atFastAbstractSub(s32) const;
template void soArrayVector<ftEntry*, 9>::setSize(s32);
