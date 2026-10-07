#pragma force_active on
#define SO_ARRAY_LIST_EXTERNAL_INDEX_MEMBERS
#include <so/so_array.h>
class wnPikminPikmin;

template s32 soArrayList<wnPikminPikmin*, 10>::size() const;
template bool soArrayList<wnPikminPikmin*, 10>::isFull() const;
template void soArrayList<wnPikminPikmin*, 10>::set(s32,wnPikminPikmin* const&,s32);
template void soArrayList<wnPikminPikmin*, 10>::clear();
template s32 soArrayList<wnPikminPikmin*, 10>::capacity() const;
