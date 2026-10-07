#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 64>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 64>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 64>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 64>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 64>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 64>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 64>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 64>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 64>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 64>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 64>::setSize(s32 size);
