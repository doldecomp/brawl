#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 31>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 31>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 31>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 31>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 31>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 31>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 31>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 31>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 31>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 31>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 31>::setSize(s32 size);
