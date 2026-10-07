#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 65>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 65>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 65>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 65>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 65>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 65>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 65>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 65>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 65>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 65>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 65>::setSize(s32 size);
