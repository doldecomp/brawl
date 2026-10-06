#pragma force_active on
#include <so/so_array.h>

class soGimmickEventObserver;

template soGimmickEventObserver*& soArrayVectorAbstract<soGimmickEventObserver*>::at(s32);
template soGimmickEventObserver* const& soArrayVectorAbstract<soGimmickEventObserver*>::at(s32) const;
template void soArrayVectorAbstract<soGimmickEventObserver*>::unshift(soGimmickEventObserver* const&);
template void soArrayVectorAbstract<soGimmickEventObserver*>::shift();
template void soArrayVectorAbstract<soGimmickEventObserver*>::pop();
template void soArrayVectorAbstract<soGimmickEventObserver*>::insert(s32, soGimmickEventObserver* const&);
template void soArrayVectorAbstract<soGimmickEventObserver*>::erase(s32);
template void soArrayVectorAbstract<soGimmickEventObserver*>::set(s32, soGimmickEventObserver* const&, s32);
template void soArrayVectorAbstract<soGimmickEventObserver*>::clear();
template bool soArrayVectorAbstract<soGimmickEventObserver*>::isNull() const;
template void soArrayVectorAbstract<soGimmickEventObserver*>::substitution(s32, s32);
