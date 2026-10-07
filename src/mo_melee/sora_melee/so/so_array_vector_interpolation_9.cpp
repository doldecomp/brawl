#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 9>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 9>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 9>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 9>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 9>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 9>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 9>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 9>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 9>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 9>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 9>::setSize(s32 size);
