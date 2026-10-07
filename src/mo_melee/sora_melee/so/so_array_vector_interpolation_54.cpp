#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 54>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 54>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 54>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 54>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 54>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 54>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 54>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 54>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 54>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 54>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 54>::setSize(s32 size);
