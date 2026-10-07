#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 39>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 39>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 39>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 39>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 39>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 39>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 39>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 39>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 39>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 39>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 39>::setSize(s32 size);
