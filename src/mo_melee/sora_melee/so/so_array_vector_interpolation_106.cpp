#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 106>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 106>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 106>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 106>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 106>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 106>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 106>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 106>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 106>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 106>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 106>::setSize(s32 size);
