#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soLinkConnection.h>

template soLinkConnection& soArrayVectorAbstract<soLinkConnection>::at(s32);
template const soLinkConnection& soArrayVectorAbstract<soLinkConnection>::at(s32) const;
template void soArrayVectorAbstract<soLinkConnection>::unshift(const soLinkConnection&);
template void soArrayVectorAbstract<soLinkConnection>::shift();
template void soArrayVectorAbstract<soLinkConnection>::push(const soLinkConnection&);
template void soArrayVectorAbstract<soLinkConnection>::pop();
template void soArrayVectorAbstract<soLinkConnection>::insert(s32, const soLinkConnection&);
template void soArrayVectorAbstract<soLinkConnection>::erase(s32);
template void soArrayVectorAbstract<soLinkConnection>::set(s32, const soLinkConnection&, s32);
template void soArrayVectorAbstract<soLinkConnection>::clear();
template bool soArrayVectorAbstract<soLinkConnection>::isNull() const;
template void soArrayVectorAbstract<soLinkConnection>::substitution(s32, s32);
