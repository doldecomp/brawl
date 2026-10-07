#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 22>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 22>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 22>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 22>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 22>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 22>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 22>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 22>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 22>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 22>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 22>::setSize(s32 size);
