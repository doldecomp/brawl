#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 3>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 3>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 3>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 3>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 3>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 3>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 3>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 3>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 3>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 3>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 3>::setSize(s32 size);
