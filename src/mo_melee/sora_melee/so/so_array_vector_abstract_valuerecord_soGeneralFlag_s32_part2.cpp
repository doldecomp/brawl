#pragma force_active on
#include <so/so_array.h>


template soGeneralFlag<s32>& soArrayVectorAbstract<soGeneralFlag<s32> >::at(s32);
template const soGeneralFlag<s32>& soArrayVectorAbstract<soGeneralFlag<s32> >::at(s32) const;
template void soArrayVectorAbstract<soGeneralFlag<s32> >::unshift(const soGeneralFlag<s32>&);
template void soArrayVectorAbstract<soGeneralFlag<s32> >::shift();
template void soArrayVectorAbstract<soGeneralFlag<s32> >::pop();
template void soArrayVectorAbstract<soGeneralFlag<s32> >::insert(s32, const soGeneralFlag<s32>&);
template void soArrayVectorAbstract<soGeneralFlag<s32> >::erase(s32);
template void soArrayVectorAbstract<soGeneralFlag<s32> >::set(s32, const soGeneralFlag<s32>&, s32);
template void soArrayVectorAbstract<soGeneralFlag<s32> >::clear();
template bool soArrayVectorAbstract<soGeneralFlag<s32> >::isNull() const;
template void soArrayVectorAbstract<soGeneralFlag<s32> >::substitution(s32, s32);
