#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 14>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 14>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 14>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 14>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 14>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 14>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 14>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 14>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 14>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 14>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 14>::setSize(s32 size);
