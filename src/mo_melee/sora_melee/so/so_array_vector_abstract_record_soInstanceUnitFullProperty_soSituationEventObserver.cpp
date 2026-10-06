#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soSituationEventObserver;

template soInstanceUnitFullProperty<soSituationEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soSituationEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soSituationEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soSituationEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soSituationEventObserver*> >::unshift(const soInstanceUnitFullProperty<soSituationEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soSituationEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soSituationEventObserver*> >::push(const soInstanceUnitFullProperty<soSituationEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soSituationEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soSituationEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soSituationEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soSituationEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soSituationEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soSituationEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soSituationEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soSituationEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soSituationEventObserver*> >::substitution(s32, s32);
