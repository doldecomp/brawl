#pragma force_active on
#define SO_ARRAY_LIST_EXTERNAL_QUERY_MEMBERS
#include <so/so_array.h>
class wnPikminPikmin;

template bool soArrayList<wnPikminPikmin*, 10>::isNull() const;
template s32 soArrayList<wnPikminPikmin*, 10>::shiftFreeArrayIndex(s32);
template s32 soArrayList<wnPikminPikmin*, 10>::getArrayIndex(s32) const;
template s32 soArrayList<wnPikminPikmin*, 10>::insertSub(s32,s32);
template void soArrayList<wnPikminPikmin*, 10>::eraseSub(s32);
