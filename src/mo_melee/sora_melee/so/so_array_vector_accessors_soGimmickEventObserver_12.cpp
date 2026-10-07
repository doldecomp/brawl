#pragma force_active on
#include <so/so_array.h>
class soGimmickEventObserver;

template s32 soArrayVector<soGimmickEventObserver*, 12>::getTopIndex() const;
template void soArrayVector<soGimmickEventObserver*, 12>::setTopIndex(s32);
template s32 soArrayVector<soGimmickEventObserver*, 12>::getLastIndex() const;
template void soArrayVector<soGimmickEventObserver*, 12>::setLastIndex(s32);
template soGimmickEventObserver*& soArrayVector<soGimmickEventObserver*, 12>::getArrayValueConst(s32);
template void soArrayVector<soGimmickEventObserver*, 12>::onFull();
template void soArrayVector<soGimmickEventObserver*, 12>::offFull();
template bool soArrayVector<soGimmickEventObserver*, 12>::isFull() const;
template s32 soArrayVector<soGimmickEventObserver*, 12>::capacity() const;
template s32 soArrayVector<soGimmickEventObserver*, 12>::size() const;
template soGimmickEventObserver*& soArrayVector<soGimmickEventObserver*, 12>::atFastAbstractSub(s32) const;
template void soArrayVector<soGimmickEventObserver*, 12>::setSize(s32);
