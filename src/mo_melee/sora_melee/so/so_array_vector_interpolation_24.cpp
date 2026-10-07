#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 24>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 24>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 24>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 24>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 24>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 24>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 24>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 24>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 24>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 24>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 24>::setSize(s32 size);
