#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
#include <so/templates/so_array_value_soTransitionTerm.h>


template soInstanceUnitFullProperty<soTransitionTerm>& soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm> >::at(s32);
template const soInstanceUnitFullProperty<soTransitionTerm>& soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm> >::unshift(const soInstanceUnitFullProperty<soTransitionTerm>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm> >::push(const soInstanceUnitFullProperty<soTransitionTerm>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm> >::insert(s32, const soInstanceUnitFullProperty<soTransitionTerm>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm> >::set(s32, const soInstanceUnitFullProperty<soTransitionTerm>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTransitionTerm> >::substitution(s32, s32);
