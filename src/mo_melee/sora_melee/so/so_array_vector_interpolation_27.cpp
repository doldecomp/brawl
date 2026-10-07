#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 27>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 27>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 27>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 27>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 27>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 27>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 27>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 27>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 27>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 27>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 27>::setSize(s32 size);
