#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 23>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 23>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 23>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 23>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 23>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 23>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 23>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 23>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 23>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 23>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 23>::setSize(s32 size);
