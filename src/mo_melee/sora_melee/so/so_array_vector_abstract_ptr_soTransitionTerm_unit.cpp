#pragma force_active on
#include <so/so_array.h>

class soTransitionTerm;
template <class T> class soInstanceUnitFullProperty;

template soInstanceUnitFullProperty<soTransitionTerm>*& soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm>*>::at(s32);
template soInstanceUnitFullProperty<soTransitionTerm>* const& soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm>*>::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm>*>::unshift(soInstanceUnitFullProperty<soTransitionTerm>* const&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm>*>::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm>*>::push(soInstanceUnitFullProperty<soTransitionTerm>* const&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm>*>::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm>*>::insert(s32, soInstanceUnitFullProperty<soTransitionTerm>* const&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm>*>::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm>*>::set(s32, soInstanceUnitFullProperty<soTransitionTerm>* const&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm>*>::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm>*>::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm>*>::substitution(s32, s32);
