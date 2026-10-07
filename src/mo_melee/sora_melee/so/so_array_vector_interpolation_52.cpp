#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 52>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 52>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 52>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 52>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 52>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 52>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 52>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 52>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 52>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 52>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 52>::setSize(s32 size);
