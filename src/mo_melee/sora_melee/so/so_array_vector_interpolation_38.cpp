#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 38>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 38>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 38>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 38>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 38>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 38>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 38>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 38>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 38>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 38>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 38>::setSize(s32 size);
