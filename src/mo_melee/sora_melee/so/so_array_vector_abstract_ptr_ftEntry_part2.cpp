#pragma force_active on
#include <so/so_array.h>

class ftEntry;

template ftEntry*& soArrayVectorAbstract<ftEntry*>::at(s32);
template ftEntry* const& soArrayVectorAbstract<ftEntry*>::at(s32) const;
template void soArrayVectorAbstract<ftEntry*>::unshift(ftEntry* const&);
template void soArrayVectorAbstract<ftEntry*>::shift();
template void soArrayVectorAbstract<ftEntry*>::pop();
template void soArrayVectorAbstract<ftEntry*>::insert(s32, ftEntry* const&);
template void soArrayVectorAbstract<ftEntry*>::set(s32, ftEntry* const&, s32);
template bool soArrayVectorAbstract<ftEntry*>::isNull() const;
template void soArrayVectorAbstract<ftEntry*>::substitution(s32, s32);
