#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 43>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 43>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 43>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 43>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 43>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 43>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 43>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 43>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 43>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 43>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 43>::setSize(s32 size);
