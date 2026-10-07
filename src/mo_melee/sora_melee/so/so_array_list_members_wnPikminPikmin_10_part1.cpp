#pragma force_active on
#define SO_ARRAY_LIST_EXTERNAL_INDEX_MEMBERS
#define SO_ARRAY_LIST_EXTERNAL_QUERY_MEMBERS
#include <so/so_array.h>
class wnPikminPikmin;

template wnPikminPikmin*& soArrayList<wnPikminPikmin*, 10>::at(s32);
template wnPikminPikmin* const& soArrayList<wnPikminPikmin*, 10>::at(s32) const;
template void soArrayList<wnPikminPikmin*, 10>::unshift(wnPikminPikmin* const&);
template void soArrayList<wnPikminPikmin*, 10>::shift();
template void soArrayList<wnPikminPikmin*, 10>::push(wnPikminPikmin* const&);
template void soArrayList<wnPikminPikmin*, 10>::pop();
template void soArrayList<wnPikminPikmin*, 10>::insert(s32,wnPikminPikmin* const&);
template void soArrayList<wnPikminPikmin*, 10>::erase(s32);
