#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 25>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 25>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 25>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 25>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 25>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 25>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 25>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 25>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 25>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 25>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 25>::setSize(s32 size);
