#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_damage.h>

template s32 soArrayVector<soDamage, 1>::getTopIndex() const;
template void soArrayVector<soDamage, 1>::setTopIndex(s32);
template s32 soArrayVector<soDamage, 1>::getLastIndex() const;
template void soArrayVector<soDamage, 1>::setLastIndex(s32);
template soDamage& soArrayVector<soDamage, 1>::getArrayValueConst(s32);
template void soArrayVector<soDamage, 1>::onFull();
template void soArrayVector<soDamage, 1>::offFull();
template bool soArrayVector<soDamage, 1>::isFull() const;
template s32 soArrayVector<soDamage, 1>::capacity() const;
template s32 soArrayVector<soDamage, 1>::size() const;
template void soArrayVector<soDamage, 1>::setSize(s32);
