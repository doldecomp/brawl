#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soTurnEventObserver;

template soInstanceUnitFullProperty<soTurnEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soTurnEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soTurnEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soTurnEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTurnEventObserver*> >::unshift(const soInstanceUnitFullProperty<soTurnEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTurnEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTurnEventObserver*> >::push(const soInstanceUnitFullProperty<soTurnEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTurnEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTurnEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soTurnEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTurnEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTurnEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soTurnEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTurnEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soTurnEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTurnEventObserver*> >::substitution(s32, s32);
