#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftWolf_PostureInfo.h>

template ftWolf::PostureInfo& soArrayVectorAbstract<ftWolf::PostureInfo>::at(s32);
template const ftWolf::PostureInfo& soArrayVectorAbstract<ftWolf::PostureInfo>::at(s32) const;
template void soArrayVectorAbstract<ftWolf::PostureInfo>::unshift(const ftWolf::PostureInfo&);
template void soArrayVectorAbstract<ftWolf::PostureInfo>::shift();
template void soArrayVectorAbstract<ftWolf::PostureInfo>::push(const ftWolf::PostureInfo&);
template void soArrayVectorAbstract<ftWolf::PostureInfo>::pop();
template void soArrayVectorAbstract<ftWolf::PostureInfo>::insert(s32, const ftWolf::PostureInfo&);
template void soArrayVectorAbstract<ftWolf::PostureInfo>::erase(s32);
template void soArrayVectorAbstract<ftWolf::PostureInfo>::set(s32, const ftWolf::PostureInfo&, s32);
template void soArrayVectorAbstract<ftWolf::PostureInfo>::clear();
template bool soArrayVectorAbstract<ftWolf::PostureInfo>::isNull() const;
template void soArrayVectorAbstract<ftWolf::PostureInfo>::substitution(s32, s32);
