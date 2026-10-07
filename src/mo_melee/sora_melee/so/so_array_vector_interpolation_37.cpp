#pragma force_active on
#include <so/posture/so_posture_module_impl.h>

template s32 soArrayVector<soInterpolation<Vec3f>, 37>::getTopIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 37>::setTopIndex(s32 topIndex);
template s32 soArrayVector<soInterpolation<Vec3f>, 37>::getLastIndex() const;
template void soArrayVector<soInterpolation<Vec3f>, 37>::setLastIndex(s32 lastIndex);
template soInterpolation<Vec3f>& soArrayVector<soInterpolation<Vec3f>, 37>::getArrayValueConst(s32 index);
template void soArrayVector<soInterpolation<Vec3f>, 37>::onFull();
template void soArrayVector<soInterpolation<Vec3f>, 37>::offFull();
template bool soArrayVector<soInterpolation<Vec3f>, 37>::isFull() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 37>::capacity() const;
template s32 soArrayVector<soInterpolation<Vec3f>, 37>::size() const;
template void soArrayVector<soInterpolation<Vec3f>, 37>::setSize(s32 size);
