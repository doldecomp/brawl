#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 76>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 76>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 76>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 76>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 76>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 76>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 76>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 76>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 76>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 76>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 76>::setSize(s32 size);
