#pragma force_active on
#include <so/so_array.h>
#include <mt/mt_vector.h>


template void soArrayVectorAbstract<Vec3f>::clear();
template bool soArrayVectorAbstract<Vec3f>::isNull() const;
template void soArrayVectorAbstract<Vec3f>::substitution(s32, s32);
