#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 61>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 61>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 61>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 61>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 61>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 61>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 61>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 61>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 61>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 61>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 61>::setSize(s32 size);
