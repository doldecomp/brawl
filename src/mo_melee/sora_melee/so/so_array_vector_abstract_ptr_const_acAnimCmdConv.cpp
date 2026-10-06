#pragma force_active on
#include <so/so_array.h>

class acAnimCmdConv;

template const acAnimCmdConv*& soArrayVectorAbstract<const acAnimCmdConv*>::at(s32);
template const acAnimCmdConv* const& soArrayVectorAbstract<const acAnimCmdConv*>::at(s32) const;
template void soArrayVectorAbstract<const acAnimCmdConv*>::unshift(const acAnimCmdConv* const&);
template void soArrayVectorAbstract<const acAnimCmdConv*>::shift();
template void soArrayVectorAbstract<const acAnimCmdConv*>::push(const acAnimCmdConv* const&);
template void soArrayVectorAbstract<const acAnimCmdConv*>::pop();
template void soArrayVectorAbstract<const acAnimCmdConv*>::insert(s32, const acAnimCmdConv* const&);
template void soArrayVectorAbstract<const acAnimCmdConv*>::erase(s32);
template void soArrayVectorAbstract<const acAnimCmdConv*>::set(s32, const acAnimCmdConv* const&, s32);
template void soArrayVectorAbstract<const acAnimCmdConv*>::clear();
template bool soArrayVectorAbstract<const acAnimCmdConv*>::isNull() const;
template void soArrayVectorAbstract<const acAnimCmdConv*>::substitution(s32, s32);
