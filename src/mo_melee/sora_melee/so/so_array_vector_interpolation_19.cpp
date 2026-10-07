#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 19>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 19>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 19>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 19>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 19>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 19>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 19>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 19>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 19>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 19>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 19>::setSize(s32 size);
