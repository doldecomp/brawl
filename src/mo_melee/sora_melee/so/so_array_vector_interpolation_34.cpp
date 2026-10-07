#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 34>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 34>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 34>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 34>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 34>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 34>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 34>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 34>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 34>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 34>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 34>::setSize(s32 size);
