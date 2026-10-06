#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftFalco_PostureInfo.h>

template ftFalco::PostureInfo& soArrayVectorAbstract<ftFalco::PostureInfo>::at(s32);
template const ftFalco::PostureInfo& soArrayVectorAbstract<ftFalco::PostureInfo>::at(s32) const;
template void soArrayVectorAbstract<ftFalco::PostureInfo>::unshift(const ftFalco::PostureInfo&);
template void soArrayVectorAbstract<ftFalco::PostureInfo>::shift();
template void soArrayVectorAbstract<ftFalco::PostureInfo>::push(const ftFalco::PostureInfo&);
template void soArrayVectorAbstract<ftFalco::PostureInfo>::pop();
template void soArrayVectorAbstract<ftFalco::PostureInfo>::insert(s32, const ftFalco::PostureInfo&);
template void soArrayVectorAbstract<ftFalco::PostureInfo>::erase(s32);
template void soArrayVectorAbstract<ftFalco::PostureInfo>::set(s32, const ftFalco::PostureInfo&, s32);
template void soArrayVectorAbstract<ftFalco::PostureInfo>::clear();
template bool soArrayVectorAbstract<ftFalco::PostureInfo>::isNull() const;
template void soArrayVectorAbstract<ftFalco::PostureInfo>::substitution(s32, s32);
