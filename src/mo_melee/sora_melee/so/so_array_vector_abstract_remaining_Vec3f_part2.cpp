#pragma force_active on
#include <so/so_array.h>
#include <mt/mt_vector.h>


template const Vec3f& soArrayVectorAbstract<Vec3f>::at(s32) const;
template void soArrayVectorAbstract<Vec3f>::unshift(const Vec3f&);
template void soArrayVectorAbstract<Vec3f>::shift();
template void soArrayVectorAbstract<Vec3f>::pop();
template void soArrayVectorAbstract<Vec3f>::insert(s32, const Vec3f&);
template void soArrayVectorAbstract<Vec3f>::erase(s32);
