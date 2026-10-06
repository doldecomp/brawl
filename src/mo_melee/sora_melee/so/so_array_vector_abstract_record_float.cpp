#pragma force_active on
#include <so/so_array.h>


template float& soArrayVectorAbstract<float>::at(s32);
template const float& soArrayVectorAbstract<float>::at(s32) const;
template void soArrayVectorAbstract<float>::unshift(const float&);
template void soArrayVectorAbstract<float>::shift();
template void soArrayVectorAbstract<float>::push(const float&);
template void soArrayVectorAbstract<float>::pop();
template void soArrayVectorAbstract<float>::insert(s32, const float&);
template void soArrayVectorAbstract<float>::erase(s32);
template void soArrayVectorAbstract<float>::set(s32, const float&, s32);
template void soArrayVectorAbstract<float>::clear();
template bool soArrayVectorAbstract<float>::isNull() const;
template void soArrayVectorAbstract<float>::substitution(s32, s32);
