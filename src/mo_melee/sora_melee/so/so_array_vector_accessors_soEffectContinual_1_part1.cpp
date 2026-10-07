#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soEffectContinual.h>

template s32 soArrayVector<soEffectContinual, 1>::getTopIndex() const;
template void soArrayVector<soEffectContinual, 1>::setTopIndex(s32);
template s32 soArrayVector<soEffectContinual, 1>::getLastIndex() const;
template void soArrayVector<soEffectContinual, 1>::setLastIndex(s32);
template soEffectContinual& soArrayVector<soEffectContinual, 1>::getArrayValueConst(s32);
template void soArrayVector<soEffectContinual, 1>::onFull();
template void soArrayVector<soEffectContinual, 1>::offFull();
template bool soArrayVector<soEffectContinual, 1>::isFull() const;
template s32 soArrayVector<soEffectContinual, 1>::capacity() const;
template s32 soArrayVector<soEffectContinual, 1>::size() const;
template void soArrayVector<soEffectContinual, 1>::setSize(s32);
