#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 2>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 2>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 2>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 2>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 2>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 2>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 2>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 2>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 2>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 2>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 2>::setSize(s32 size);
