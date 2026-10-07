#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_camera_subject.h>

template s32 soArrayVector<soCameraSubject, 1>::getTopIndex() const;
template void soArrayVector<soCameraSubject, 1>::setTopIndex(s32);
template s32 soArrayVector<soCameraSubject, 1>::getLastIndex() const;
template void soArrayVector<soCameraSubject, 1>::setLastIndex(s32);
template soCameraSubject& soArrayVector<soCameraSubject, 1>::getArrayValueConst(s32);
template void soArrayVector<soCameraSubject, 1>::onFull();
template void soArrayVector<soCameraSubject, 1>::offFull();
template bool soArrayVector<soCameraSubject, 1>::isFull() const;
template s32 soArrayVector<soCameraSubject, 1>::capacity() const;
template s32 soArrayVector<soCameraSubject, 1>::size() const;
template void soArrayVector<soCameraSubject, 1>::setSize(s32);
