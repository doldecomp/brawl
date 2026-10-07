#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 28>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 28>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 28>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 28>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 28>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 28>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 28>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 28>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 28>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 28>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 28>::setSize(s32 size);
