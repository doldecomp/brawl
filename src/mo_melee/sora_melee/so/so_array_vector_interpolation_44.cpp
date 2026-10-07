#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 44>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 44>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 44>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 44>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 44>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 44>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 44>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 44>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 44>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 44>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 44>::setSize(s32 size);
