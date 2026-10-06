#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soItemInfo.h>

template soItemInfo& soArrayVectorAbstract<soItemInfo>::at(s32);
template const soItemInfo& soArrayVectorAbstract<soItemInfo>::at(s32) const;
template void soArrayVectorAbstract<soItemInfo>::unshift(const soItemInfo&);
template void soArrayVectorAbstract<soItemInfo>::shift();
template void soArrayVectorAbstract<soItemInfo>::push(const soItemInfo&);
template void soArrayVectorAbstract<soItemInfo>::pop();
template void soArrayVectorAbstract<soItemInfo>::insert(s32, const soItemInfo&);
template void soArrayVectorAbstract<soItemInfo>::erase(s32);
template void soArrayVectorAbstract<soItemInfo>::set(s32, const soItemInfo&, s32);
template void soArrayVectorAbstract<soItemInfo>::clear();
template bool soArrayVectorAbstract<soItemInfo>::isNull() const;
template void soArrayVectorAbstract<soItemInfo>::substitution(s32, s32);
