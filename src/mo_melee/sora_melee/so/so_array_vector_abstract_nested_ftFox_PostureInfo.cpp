#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftFox_PostureInfo.h>

template ftFox::PostureInfo& soArrayVectorAbstract<ftFox::PostureInfo>::at(s32);
template const ftFox::PostureInfo& soArrayVectorAbstract<ftFox::PostureInfo>::at(s32) const;
template void soArrayVectorAbstract<ftFox::PostureInfo>::unshift(const ftFox::PostureInfo&);
template void soArrayVectorAbstract<ftFox::PostureInfo>::shift();
template void soArrayVectorAbstract<ftFox::PostureInfo>::push(const ftFox::PostureInfo&);
template void soArrayVectorAbstract<ftFox::PostureInfo>::pop();
template void soArrayVectorAbstract<ftFox::PostureInfo>::insert(s32, const ftFox::PostureInfo&);
template void soArrayVectorAbstract<ftFox::PostureInfo>::erase(s32);
template void soArrayVectorAbstract<ftFox::PostureInfo>::set(s32, const ftFox::PostureInfo&, s32);
template void soArrayVectorAbstract<ftFox::PostureInfo>::clear();
template bool soArrayVectorAbstract<ftFox::PostureInfo>::isNull() const;
template void soArrayVectorAbstract<ftFox::PostureInfo>::substitution(s32, s32);
