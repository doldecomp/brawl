#pragma force_active on
#include <so/so_array.h>
class wnemSimple;

template s32 soArrayVector<wnemSimple*, 10>::getTopIndex() const;
template void soArrayVector<wnemSimple*, 10>::setTopIndex(s32);
template s32 soArrayVector<wnemSimple*, 10>::getLastIndex() const;
template void soArrayVector<wnemSimple*, 10>::setLastIndex(s32);
template wnemSimple*& soArrayVector<wnemSimple*, 10>::getArrayValueConst(s32);
template void soArrayVector<wnemSimple*, 10>::onFull();
template void soArrayVector<wnemSimple*, 10>::offFull();
template bool soArrayVector<wnemSimple*, 10>::isFull() const;
template s32 soArrayVector<wnemSimple*, 10>::capacity() const;
template s32 soArrayVector<wnemSimple*, 10>::size() const;
template void soArrayVector<wnemSimple*, 10>::setSize(s32);
