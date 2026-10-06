#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soTargetSearchRayCheckCache.h>

template soTargetSearchRayCheckCache& soArrayVectorAbstract<soTargetSearchRayCheckCache>::at(s32);
template const soTargetSearchRayCheckCache& soArrayVectorAbstract<soTargetSearchRayCheckCache>::at(s32) const;
template void soArrayVectorAbstract<soTargetSearchRayCheckCache>::unshift(const soTargetSearchRayCheckCache&);
template void soArrayVectorAbstract<soTargetSearchRayCheckCache>::shift();
template void soArrayVectorAbstract<soTargetSearchRayCheckCache>::push(const soTargetSearchRayCheckCache&);
template void soArrayVectorAbstract<soTargetSearchRayCheckCache>::pop();
template void soArrayVectorAbstract<soTargetSearchRayCheckCache>::insert(s32, const soTargetSearchRayCheckCache&);
template void soArrayVectorAbstract<soTargetSearchRayCheckCache>::erase(s32);
template void soArrayVectorAbstract<soTargetSearchRayCheckCache>::set(s32, const soTargetSearchRayCheckCache&, s32);
template void soArrayVectorAbstract<soTargetSearchRayCheckCache>::clear();
template bool soArrayVectorAbstract<soTargetSearchRayCheckCache>::isNull() const;
template void soArrayVectorAbstract<soTargetSearchRayCheckCache>::substitution(s32, s32);
