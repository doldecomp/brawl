#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 12>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 12>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 12>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 12>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 12>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 12>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 12>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 12>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 12>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 12>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 12>::setSize(s32 size);
