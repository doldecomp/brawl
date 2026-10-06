#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_camera_subject.h>


template soCameraSubject& soArrayVectorAbstract<soCameraSubject>::at(s32);
template const soCameraSubject& soArrayVectorAbstract<soCameraSubject>::at(s32) const;
template void soArrayVectorAbstract<soCameraSubject>::unshift(const soCameraSubject&);
template void soArrayVectorAbstract<soCameraSubject>::shift();
template void soArrayVectorAbstract<soCameraSubject>::push(const soCameraSubject&);
template void soArrayVectorAbstract<soCameraSubject>::pop();
template void soArrayVectorAbstract<soCameraSubject>::insert(s32, const soCameraSubject&);
template void soArrayVectorAbstract<soCameraSubject>::erase(s32);
template void soArrayVectorAbstract<soCameraSubject>::set(s32, const soCameraSubject&, s32);
template void soArrayVectorAbstract<soCameraSubject>::clear();
template bool soArrayVectorAbstract<soCameraSubject>::isNull() const;
template void soArrayVectorAbstract<soCameraSubject>::substitution(s32, s32);
