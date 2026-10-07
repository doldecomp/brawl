#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 115>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 115>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 115>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 115>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 115>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 115>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 115>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 115>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 115>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 115>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 115>::setSize(s32 size);
