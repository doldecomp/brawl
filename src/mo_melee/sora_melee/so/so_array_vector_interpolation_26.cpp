#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 26>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 26>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 26>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 26>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 26>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 26>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 26>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 26>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 26>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 26>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 26>::setSize(s32 size);
