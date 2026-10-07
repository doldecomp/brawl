#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 33>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 33>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 33>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 33>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 33>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 33>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 33>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 33>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 33>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 33>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 33>::setSize(s32 size);
