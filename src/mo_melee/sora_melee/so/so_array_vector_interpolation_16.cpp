#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 16>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 16>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 16>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 16>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 16>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 16>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 16>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 16>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 16>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 16>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 16>::setSize(s32 size);
