#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_damage.h>

template s32 soArrayVector<soDamage, 3>::getTopIndex() const;
template void soArrayVector<soDamage, 3>::setTopIndex(s32);
template s32 soArrayVector<soDamage, 3>::getLastIndex() const;
template void soArrayVector<soDamage, 3>::setLastIndex(s32);
template soDamage& soArrayVector<soDamage, 3>::getArrayValueConst(s32);
template void soArrayVector<soDamage, 3>::onFull();
template void soArrayVector<soDamage, 3>::offFull();
template bool soArrayVector<soDamage, 3>::isFull() const;
template s32 soArrayVector<soDamage, 3>::capacity() const;
template s32 soArrayVector<soDamage, 3>::size() const;
template soDamage& soArrayVector<soDamage, 3>::atFastAbstractSub(s32) const;
template void soArrayVector<soDamage, 3>::setSize(s32);
