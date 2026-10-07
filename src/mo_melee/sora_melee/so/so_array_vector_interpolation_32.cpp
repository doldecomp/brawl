#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 32>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 32>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 32>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 32>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 32>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 32>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 32>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 32>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 32>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 32>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 32>::setSize(s32 size);
