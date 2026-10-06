#pragma force_active on
#include <so/so_array.h>


template u32& soArrayVectorAbstract<u32>::at(s32);
template const u32& soArrayVectorAbstract<u32>::at(s32) const;
template void soArrayVectorAbstract<u32>::unshift(const u32&);
template void soArrayVectorAbstract<u32>::shift();
template void soArrayVectorAbstract<u32>::pop();
template void soArrayVectorAbstract<u32>::insert(s32, const u32&);
template void soArrayVectorAbstract<u32>::erase(s32);
template void soArrayVectorAbstract<u32>::set(s32, const u32&, s32);
template void soArrayVectorAbstract<u32>::clear();
template bool soArrayVectorAbstract<u32>::isNull() const;
template void soArrayVectorAbstract<u32>::substitution(s32, s32);
