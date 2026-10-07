#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soTargetSearchRayCheckCache.h>

template s32 soArrayVector<soTargetSearchRayCheckCache, 8>::getTopIndex() const;
template void soArrayVector<soTargetSearchRayCheckCache, 8>::setTopIndex(s32);
template s32 soArrayVector<soTargetSearchRayCheckCache, 8>::getLastIndex() const;
template void soArrayVector<soTargetSearchRayCheckCache, 8>::setLastIndex(s32);
template soTargetSearchRayCheckCache& soArrayVector<soTargetSearchRayCheckCache, 8>::getArrayValueConst(s32);
template void soArrayVector<soTargetSearchRayCheckCache, 8>::onFull();
template void soArrayVector<soTargetSearchRayCheckCache, 8>::offFull();
template bool soArrayVector<soTargetSearchRayCheckCache, 8>::isFull() const;
template s32 soArrayVector<soTargetSearchRayCheckCache, 8>::capacity() const;
template s32 soArrayVector<soTargetSearchRayCheckCache, 8>::size() const;
template void soArrayVector<soTargetSearchRayCheckCache, 8>::setSize(s32);
