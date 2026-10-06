#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soTransitionTermPack.h>


template soTransitionTermPack& soArrayVectorAbstract<soTransitionTermPack>::at(s32);
template const soTransitionTermPack& soArrayVectorAbstract<soTransitionTermPack>::at(s32) const;
template void soArrayVectorAbstract<soTransitionTermPack>::unshift(const soTransitionTermPack&);
template void soArrayVectorAbstract<soTransitionTermPack>::shift();
template void soArrayVectorAbstract<soTransitionTermPack>::push(const soTransitionTermPack&);
template void soArrayVectorAbstract<soTransitionTermPack>::pop();
template void soArrayVectorAbstract<soTransitionTermPack>::insert(s32, const soTransitionTermPack&);
template void soArrayVectorAbstract<soTransitionTermPack>::erase(s32);
template void soArrayVectorAbstract<soTransitionTermPack>::set(s32, const soTransitionTermPack&, s32);
template void soArrayVectorAbstract<soTransitionTermPack>::clear();
template bool soArrayVectorAbstract<soTransitionTermPack>::isNull() const;
template void soArrayVectorAbstract<soTransitionTermPack>::substitution(s32, s32);
