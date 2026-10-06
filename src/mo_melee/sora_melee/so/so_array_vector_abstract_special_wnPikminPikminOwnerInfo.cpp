#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_wnPikminPikminOwnerInfo.h>


template wnPikminPikminOwnerInfo& soArrayVectorAbstract<wnPikminPikminOwnerInfo>::at(s32);
template const wnPikminPikminOwnerInfo& soArrayVectorAbstract<wnPikminPikminOwnerInfo>::at(s32) const;
template void soArrayVectorAbstract<wnPikminPikminOwnerInfo>::unshift(const wnPikminPikminOwnerInfo&);
template void soArrayVectorAbstract<wnPikminPikminOwnerInfo>::shift();
template void soArrayVectorAbstract<wnPikminPikminOwnerInfo>::push(const wnPikminPikminOwnerInfo&);
template void soArrayVectorAbstract<wnPikminPikminOwnerInfo>::pop();
template void soArrayVectorAbstract<wnPikminPikminOwnerInfo>::insert(s32, const wnPikminPikminOwnerInfo&);
template void soArrayVectorAbstract<wnPikminPikminOwnerInfo>::erase(s32);
template void soArrayVectorAbstract<wnPikminPikminOwnerInfo>::set(s32, const wnPikminPikminOwnerInfo&, s32);
template void soArrayVectorAbstract<wnPikminPikminOwnerInfo>::clear();
template bool soArrayVectorAbstract<wnPikminPikminOwnerInfo>::isNull() const;
template void soArrayVectorAbstract<wnPikminPikminOwnerInfo>::substitution(s32, s32);
