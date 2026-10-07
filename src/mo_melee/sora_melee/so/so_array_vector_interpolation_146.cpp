#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 146>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 146>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 146>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 146>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 146>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 146>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 146>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 146>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 146>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 146>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 146>::setSize(s32 size);
