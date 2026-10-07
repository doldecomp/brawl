#pragma force_active on
#include <so/so_array.h>
#include <mt/mt_vector.h>

template s32 soArrayVector<Vec3f, 1>::getTopIndex() const;
template void soArrayVector<Vec3f, 1>::setTopIndex(s32);
template s32 soArrayVector<Vec3f, 1>::getLastIndex() const;
template void soArrayVector<Vec3f, 1>::setLastIndex(s32);
template Vec3f& soArrayVector<Vec3f, 1>::getArrayValueConst(s32);
template void soArrayVector<Vec3f, 1>::onFull();
template void soArrayVector<Vec3f, 1>::offFull();
template bool soArrayVector<Vec3f, 1>::isFull() const;
template s32 soArrayVector<Vec3f, 1>::capacity() const;
template s32 soArrayVector<Vec3f, 1>::size() const;
template Vec3f& soArrayVector<Vec3f, 1>::atFastAbstractSub(s32) const;
template void soArrayVector<Vec3f, 1>::setSize(s32);
